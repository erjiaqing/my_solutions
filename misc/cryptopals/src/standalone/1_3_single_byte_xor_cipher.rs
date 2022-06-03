use cryptopals::set1::*;

fn main() {
    let original = hex_to_bytes(&String::from(
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736",
    ));
    let original_len = original.len();
    let mut max_score = -1.;
    let mut answer: Vec<u8> = vec![];
    for i in 0..=255 {
        let key = vec![i; original_len];
        let decrypted = fixed_xor(&key, &original);
        let decrypted_score = sentense_score(&decrypted);

        if max_score < decrypted_score {
            max_score = decrypted_score;
            answer = decrypted;
        }
    }

    println!("{:?} (score {})", String::from_utf8(answer), max_score);
}
