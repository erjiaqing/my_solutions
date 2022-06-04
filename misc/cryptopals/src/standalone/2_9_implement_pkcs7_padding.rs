use cryptopals::set2::*;

fn main() {
    assert_eq!(
        pkcs7_padding(&"YELLOW SUBMARINE".as_bytes().to_vec(), 20),
        "YELLOW SUBMARINE\x04\x04\x04\x04".as_bytes().to_vec()
    )
}
