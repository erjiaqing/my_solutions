use std::io;
use std::io::prelude::*;

use cryptopals::set1::*;
use cryptopals::set2::*;
use cryptopals::util::*;

fn random_encrypt(buf: &[u8]) -> (Vec<u8>, bool) {
    let ecbmode = (rand::random::<u8>() % 2) == 0;

    let key = random_bytes(16);
    let iv = random_bytes(16);
    let padding_begin = random_bytes((rand::random::<u8>() % 5 + 5) as usize);
    let padding_end = random_bytes((rand::random::<u8>() % 5 + 5) as usize);

    let mut buf2 = vec![0; buf.len() + padding_begin.len() + padding_end.len()];
    buf2[..padding_begin.len()].copy_from_slice(&padding_begin);
    buf2[padding_begin.len()..buf.len() + padding_begin.len()].copy_from_slice(&buf);
    buf2[padding_begin.len() + buf.len()..padding_begin.len() + padding_end.len() + buf.len()]
        .copy_from_slice(&padding_end);

    if ecbmode {
        return (aes_128_ecb_encrypt(&key, &buf2), ecbmode);
    } else {
        return (aes_128_cbc_encrypt(&key, &buf2, &iv), ecbmode);
    }
}

fn main() {
    let mut buf: Vec<u8> = vec![];
    io::stdin().read_to_end(&mut buf).unwrap();

    let (cipher, mode) = random_encrypt(&buf);

    println!("Actual Mode: {} Detected Mode: {}", mode, aes_128_ecb_detect(&cipher));
}
