use cryptopals::set1::*;
use std::collections::HashMap;

fn score(v: &Vec<u8>) -> f32 {
    // https://en.wikipedia.org/wiki/Letter_frequency
    let rank = vec![
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406,
        6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074,
        0.,
    ];

    let mut count: HashMap<u8, u32> = HashMap::new();

    let mut result: f32 = 0.;
    let mut total: f32 = 0.;

    for val in v {
        let mut new_val = 26;
        let val_char = *val as char;
        if 'a' <= val_char && val_char <= 'z' {
            new_val = val - 'a' as u8;
            total += 1.;
        } else if 'A' <= val_char && val_char <= 'A' {
            new_val = val - 'A' as u8;
            total += 1.;
        } else if *val < 32 || *val >= 123 || (*val >= 91 && *val <= 96) {
            return -1.;
        }
        let c = count.entry(new_val).or_insert(0);
        *c += 1
    }

    for (k, v) in &count {
        result += ((*v as f32) / total) * rank[*k as usize];
    }

    return result;
}

fn main() {
    let original = hex_to_bytes(String::from(
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736",
    ));
    let original_len = original.len();
    let mut max_score = -1.;
    let mut answer: Vec<u8> = vec![];
    for i in 0..=255 {
        let key = vec![i; original_len];
        let decrypted = fixed_xor(&key, &original);
        let decrypted_score = score(&decrypted);

        if max_score < decrypted_score {
            max_score = decrypted_score;
            answer = decrypted;
        }
    }

    println!("{:?} (score {})", String::from_utf8(answer), max_score);
}
