use crate::set1::*;
use openssl::cipher::Cipher;
use openssl::cipher_ctx::CipherCtx;
use std::vec;
use std::vec::Vec;
use std::error::Error;

pub fn pkcs7_padding(v: &[u8], blocksize: usize) -> Vec<u8> {
    let mut ret = v.to_vec();
    let mut cnt = blocksize - ret.len() % blocksize;
    if cnt == 0 {
        cnt = blocksize;
    }
    for _ in 0..cnt {
        ret.push(cnt as u8);
    }

    return ret;
}

pub fn pkcs7_unpadding(v: &[u8]) -> Result<&[u8], &'static str> {
    if v.len() == 0 {
        return Err("null input");
    }

    let npadding = v[v.len() - 1] as usize;
    if npadding > v.len() {
        return Err("incorrect padding");
    }

    for i in 1..=npadding {
        if v[v.len() - i] as usize != npadding {
            return Err("incorrect padding");
        }
    }

    return Ok(&v[..v.len() - npadding])
}

pub fn pkcs7_unpadding_vec(mut v: Vec<u8>) -> Result<Vec<u8>, &'static str> {
    if v.len() == 0 {
        return Err("null input");
    }

    let npadding = v[v.len() - 1] as usize;
    if npadding > v.len() {
        return Err("incorrect padding");
    }

    for i in 1..=npadding {
        if v[v.len() - i] as usize != npadding {
            return Err("incorrect padding");
        }
    }

    for _ in 0..npadding {
        v.pop();
    }

    return Ok(v)
}

pub fn aes_128_ecb_encrypt_block(key: &[u8], plaintext: &[u8]) -> Vec<u8> {
    let mut ret = vec![];
    let mut ctx = CipherCtx::new().unwrap();
    ctx.encrypt_init(Some(Cipher::aes_128_ecb()), Some(key), Option::None)
        .unwrap();
    ctx.set_padding(false);
    ctx.cipher_update_vec(&plaintext, &mut ret).unwrap();
    return ret;
}

pub fn aes_128_ecb_decrypt_block(key: &[u8], ciphertext: &[u8]) -> Vec<u8> {
    let mut ret = vec![];
    let mut ctx = CipherCtx::new().unwrap();
    ctx.decrypt_init(Some(Cipher::aes_128_ecb()), Some(key), Option::None)
        .unwrap();
    ctx.set_padding(false);
    ctx.cipher_update_vec(&ciphertext, &mut ret).unwrap();
    return ret;
}

pub fn aes_128_cbc_decrypt_no_padding(key: &[u8], cipher: &[u8], iv: &[u8]) -> Vec<u8> {
    let mut plain = vec![0; cipher.len()];
    let mut last_cipher: &[u8] = iv;
    let block_size = key.len();
    let block_count = cipher.len() / block_size;
    let mut block_start = 0;
    let mut block_end = block_size;
    for _ in 0..block_count {
        let current_cipher = &cipher[block_start..block_end];
        plain[block_start..block_end].clone_from_slice(&fixed_xor(
            &aes_128_ecb_decrypt_block(key, current_cipher),
            last_cipher,
        ));
        last_cipher = current_cipher;
        block_start += block_size;
        block_end += block_size;
    }
    return plain;
}

pub fn aes_128_cbc_encrypt_no_padding(key: &[u8], plaintext: &[u8], iv: &[u8]) -> Vec<u8> {
    let mut cipher = vec![0; plaintext.len()];
    let mut last_cipher: &[u8] = iv;
    let block_size = key.len();
    let block_count = plaintext.len() / block_size;
    let mut block_start = 0;
    let mut block_end = block_size;
    for _ in 0..block_count {
        let current_block = fixed_xor(&plaintext[block_start..block_end], last_cipher);
        cipher[block_start..block_end]
            .clone_from_slice(&aes_128_ecb_encrypt_block(key, &current_block));
        last_cipher = &cipher[block_start..block_end];
        block_start += block_size;
        block_end += block_size;
    }
    return cipher;
}

pub fn aes_128_ecb_encrypt_no_padding(key: &[u8], plaintext: &[u8]) -> Vec<u8> {
    let mut cipher = vec![0; plaintext.len()];
    let block_count = plaintext.len() / 16;
    for i in 0..block_count {
        let block_start = i * 16;
        let block_end = (i + 1) * 16;
        cipher[block_start..block_end].clone_from_slice(&aes_128_ecb_encrypt_block(
            key,
            &plaintext[block_start..block_end],
        ));
    }
    return cipher;
}

pub fn aes_128_ecb_decrypt_no_padding(key: &[u8], plaintext: &[u8]) -> Vec<u8> {
    let mut cipher = vec![0; plaintext.len()];
    let block_count = plaintext.len() / 16;
    for i in 0..block_count {
        let block_start = i * 16;
        let block_end = (i + 1) * 16;
        cipher[block_start..block_end].clone_from_slice(&aes_128_ecb_decrypt_block(
            key,
            &plaintext[block_start..block_end],
        ));
    }
    return cipher;
}

pub fn aes_128_ecb_encrypt(key: &[u8], plaintext: &[u8]) -> Vec<u8> {
    return aes_128_ecb_encrypt_no_padding(key, &pkcs7_padding(plaintext, 16));
}

pub fn aes_128_cbc_encrypt(key: &[u8], plaintext: &[u8], iv: &[u8]) -> Vec<u8> {
    return aes_128_cbc_encrypt_no_padding(key, &pkcs7_padding(plaintext, 16), iv);
}

pub fn aes_128_ecb_decrypt(key: &[u8], cipher: &[u8]) -> Vec<u8> {
    return pkcs7_unpadding_vec(aes_128_ecb_decrypt_no_padding(key, cipher)).unwrap();
}

pub fn aes_128_cbc_decrypt(key: &[u8], cipher: &[u8], iv: &[u8]) -> Vec<u8> {
    let mut padded = aes_128_cbc_decrypt_no_padding(key, cipher, iv);
    let padding_len = padded[padded.len() - 1];
    for _ in 0..padding_len {
        padded.pop();
    }
    return padded;
}

pub fn aes_128_ecb_detect(cipher: &[u8]) -> bool {
    let blocks = cipher.len() / 16;
    let avg_distance = 16 * 8 / 2;
    let mut sum_distance: f32 = 0.;

    // Too lazy to calculate the actual number
    let mut total_block_pairs = 0;

    for i in 1..(blocks - 1) {
        let block_i_begin = i * 16;
        let block_i_end = (i + 1) * 16;
        let block_i = &cipher[block_i_begin..block_i_end];

        for j in (i + 1)..(blocks - 1) {
            let block_j_begin = j * 16;
            let block_j_end = (j + 1) * 16;

            let distance = edit_distance(block_i, &cipher[block_j_begin..block_j_end]);

            sum_distance += distance as f32;
            total_block_pairs += 1;

            println!("Distance {}<->{} = {}", i, j, distance);
        }
    }

    let cipher_avg_distance = sum_distance / (total_block_pairs as f32);

    println!("cipher avg distance {}", cipher_avg_distance);

    return cipher_avg_distance < (avg_distance as f32);
}
