use std::io;
use std::io::prelude::*;

use cryptopals::set1::*;
use cryptopals::set2::*;
use cryptopals::util::*;

fn enc_profile(random_key: &[u8], email: String) -> Vec<u8> {
    let formatted = format!("email={}&uid=10&role=user", email);
    return aes_128_ecb_encrypt(&random_key, &formatted.as_bytes());
}


fn dec_profile(random_key: &[u8], cipher: &[u8]) -> Vec<u8> {
    return aes_128_ecb_decrypt(&random_key, &cipher);
}

fn main() {
    let random_key: Vec<u8> = random_bytes(16);

    let cipher1 = enc_profile(&random_key, String::from("admin@adm.com"));
    let cipher2 = enc_profile(&random_key, String::from("admin@adm.admin"));

    let res = dec_profile(&random_key, &[&cipher1[..32], &cipher2[16..32], &cipher1[32..]].concat());

    println!("{:?}", String::from_utf8(dec_profile(&random_key, &cipher1)));
    println!("{:?}", String::from_utf8(dec_profile(&random_key, &cipher2)));

    println!("{:?}", String::from_utf8(res));
}
