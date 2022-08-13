use cryptopals::set2::*;
use cryptopals::util::*;
use twoway;

fn main() {
    let unknown_key = &random_bytes(16);

    let encrypt = |x: &[u8]| -> Vec<u8> {
        return aes_128_cbc_encrypt(unknown_key, x, &random_bytes(16));
    };
    
    let decrypt = |x: &[u8]| -> Vec<u8> {
        return aes_128_cbc_decrypt(unknown_key, &x[16..], &x[..16]);
    };
    
    let check = |x: &[u8]| -> bool {
        return twoway::find_bytes(&decrypt(x), ";admin=true;".as_bytes()).is_some();
    };

    let do_encrypt = |x: &str| -> Vec<u8> {
        return encrypt(&["comment1=cooking%20MCs;userdata=".as_bytes(), x.as_bytes(), ";comment2=%20like%20a%20pound%20of%20bacon".as_bytes()].concat());
    };

    // comment1=cooking%20MCs;userdata=00000000000000000admin0true;comment2=%20like%20a%20pound%20of%20bacon
    // ........--------........--------........--------........--------........--------........-----

    let mut val = do_encrypt("00000000000000000admin0true");
    val[16 + 8 * 2] ^= ('0' as u8) ^ (';' as u8);
    val[16 + 8 * 2 + 6] ^= ('0' as u8) ^ ('=' as u8);

    assert_eq!(check(&val), true);
}
