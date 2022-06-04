


pub fn random_bytes(len : usize) -> Vec<u8> {
    return vec![0; len].iter().map(|_| {rand::random::<u8>()}).collect();
}