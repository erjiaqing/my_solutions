use std::io;
use std::io::prelude::*;

use cryptopals::set1::*;
use cryptopals::set2::*;
use cryptopals::util::*;

fn main() {
    let mut buf: Vec<u8> = vec![];
    io::stdin().read_to_end(&mut buf).unwrap();

    let key = random_bytes(16);
    let padding_begin = random_bytes((rand::random::<u8>() % 5 + 5) as usize);
    let padding_end = random_bytes((rand::random::<u8>() % 5 + 5) as usize);

    let mut buf2 = vec![0; buf.len() + padding_begin.len() + padding_end.len()];
    buf2[..padding_begin.len()].copy_from_slice(&padding_begin);
    buf2[padding_begin.len()..buf.len() + padding_begin.len()].copy_from_slice(&buf);
    buf2[padding_begin.len() + buf.len()..padding_begin.len() + padding_end.len() + buf.len()]
        .copy_from_slice(&padding_end);
    let buf = pkcs7_padding(&buf2, 16);
    let blocks = buf.len() / 16;

    let mut cipher = vec![0; buf.len()];
    let mut cipher_modes = vec![];

    for i in 0..blocks {
        let block_begin = i * 16;
        let block_end = (i + 1) * 16;

        let cipher_mode = rand::random::<u8>() % 2;

        if cipher_mode == 0 {
            // ECB
            cipher[block_begin..block_end].copy_from_slice(&aes_128_ecb_encrypt_block(
                &key,
                &buf[block_begin..block_end],
            ));
        } else {
            // CBC
            cipher[block_begin..block_end].copy_from_slice(&aes_128_cbc_encrypt_no_padding(
                &key,
                &buf[block_begin..block_end],
                &random_bytes(16),
            ));
        }
        cipher_modes.push(cipher_mode);
    }

    let avg_distance = 16 * 8 / 2;

    for i in 0..blocks {
        let block_i_begin = i * 16;
        let block_i_end = (i + 1) * 16;
        let block_i = &cipher[block_i_begin..block_i_end];
        let mut smaller_than_avg = 0;
        let mut larger_than_avg = 0;

        for j in 0..blocks {
            let block_j_begin = j * 16;
            let block_j_end = (j + 1) * 16;

            if i == j {
                continue;
            }

            if edit_distance(block_i, &cipher[block_j_begin..block_j_end]) < avg_distance {
                smaller_than_avg += 1
            } else {
                larger_than_avg += 1
            }
        }

        println!(
            "Block #{} {}:{} ECB {} - {}",
            i,
            smaller_than_avg,
            larger_than_avg,
            smaller_than_avg > larger_than_avg,
            cipher_modes[i] == 0
        );
    }
}
