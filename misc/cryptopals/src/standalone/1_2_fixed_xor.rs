use cryptopals::set1::*;

fn main() {
    assert_eq!(
        bytes_to_hex(fixed_xor(
            &hex_to_bytes(String::from("1c0111001f010100061a024b53535009181c")),
            &hex_to_bytes(String::from("686974207468652062756c6c277320657965"))
        )),
        String::from("746865206b696420646f6e277420706c6179")
    );
}
