use std::io;
use std::io::prelude::*;

use cryptopals::set1::*;
use cryptopals::set2::*;
use cryptopals::util::*;

fn main() {
    let mut buf: Vec<u8> = vec![];
    io::stdin().read_to_end(&mut buf).unwrap();

    let unknown_string = base64_to_bytes(String::from_utf8_lossy(&buf).to_string());
    let unknown_key = random_bytes(16);

    let do_encrypt_inner = |buf: &[u8]| -> Vec<u8> {
        return aes_128_ecb_encrypt(&unknown_key, &buf);
    };
    let do_encrypt = |prefix: &[u8]| -> Vec<u8> {
        return do_encrypt_inner(&[prefix, unknown_string.as_slice()].concat());
    };

    let mut block_size = 0;
    let cipher_size = do_encrypt(&vec![]).len();

    // Try to get the block size
    {
        let mut buffer_size_change_i = 0;
        let mut encrypted_buffer_size = cipher_size;

        for i in 1..32 {
            let new_size = do_encrypt(&vec!['A' as u8; i]).len();

            if new_size != encrypted_buffer_size {
                if buffer_size_change_i == 0 {
                    buffer_size_change_i = i;
                    encrypted_buffer_size = new_size;
                } else {
                    block_size = i - buffer_size_change_i;
                    encrypted_buffer_size = new_size;
                    buffer_size_change_i = i;
                }
            }

            println!("{} bytes appended crypto text size {}", i, new_size);
        }
        println!("Block Size: {}", block_size);
    }

    {
        assert_eq!(aes_128_ecb_detect(&do_encrypt(&vec![])), true);
        println!("Is ECB mode.");
    }

    let mut plain_text = Vec::new();
    {
        let block_count = cipher_size / block_size;
        let mut last_block = vec!['A' as u8; block_size];
        for j in 0..block_count {
            let mut block = Vec::new();
            for i in 1..=block_size {
                let probe_first_block_enc = do_encrypt(&last_block[i..]);

                for ch in 0..128 {
                    let probe_block = do_encrypt(&[&last_block[i..], &block, &[ch as u8]].concat());

                    if probe_block[0..block_size]
                        == probe_first_block_enc[j * block_size + 0..(j + 1) * block_size]
                    {
                        println!(
                            "Block {} Byte {}: {}",
                            j,
                            i,
                            char::from_u32(ch as u32).unwrap()
                        );
                        block.push(ch as u8);
                        plain_text.push(ch as u8);
                        break;
                    }
                }
            }
            last_block = block;
        }
    }

    println!("Decrypted text:\n{}", String::from_utf8_lossy(&plain_text));
}
