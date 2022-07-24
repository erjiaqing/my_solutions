use cryptopals::set2::*;

fn main() {
    assert_eq!(
        pkcs7_unpadding_vec("YELLOW SUBMARINE\x04\x04\x04\x04".as_bytes().to_vec()).unwrap(),
        "YELLOW SUBMARINE".as_bytes().to_vec()
    );
    assert_eq!(
        pkcs7_unpadding_vec("YELLOW SUBMARINE\x05\x05\x05\x05".as_bytes().to_vec()).is_err(),
        true
    );
    assert_eq!(
        pkcs7_unpadding_vec("YELLOW SUBMARINE\x01\x02\x03\x04".as_bytes().to_vec()).is_err(),
        true
    );
}
