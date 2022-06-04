use std::collections::HashMap;
use std::vec::Vec;

pub fn hex_to_byte(c: u8) -> u8 {
    if '0' as u8 <= c && c <= '9' as u8 {
        return c - ('0' as u8);
    } else if 'a' as u8 <= c && c <= 'f' as u8 {
        return c - ('a' as u8) + 10;
    } else if 'A' as u8 <= c && c <= 'F' as u8 {
        return c - ('A' as u8) + 10;
    } else {
        return 0;
    }
}

pub fn hex_to_bytes(s: &String) -> Vec<u8> {
    let mut v: Vec<u8> = Vec::new();

    let string_bytes = s.as_bytes();

    for i in 0..string_bytes.len() / 2 {
        let hi = hex_to_byte(string_bytes[i * 2]);
        let lo = hex_to_byte(string_bytes[i * 2 + 1]);
        v.push((hi << 4) | lo)
    }

    return v;
}

pub fn bytes_to_hex(v: &Vec<u8>) -> String {
    let mut s: String = String::new();

    for val in v {
        let hi = (val >> 4) & 0xf;
        let lo = val & 0xf;

        if hi < 10 {
            s.push((('0' as u8) + hi) as char);
        } else {
            s.push((('a' as u8) + hi - 10) as char);
        }

        if lo < 10 {
            s.push((('0' as u8) + lo) as char);
        } else {
            s.push((('a' as u8) + lo - 10) as char);
        }
    }

    return s;
}

pub fn bytes_to_base64(v: &Vec<u8>) -> String {
    let mut s: String = String::new();
    let base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/".as_bytes();

    let mut reg: u32 = 0;
    let mut index: u8 = 0;

    for val in v {
        if index == 0 {
            reg = reg | ((*val as u32) << 16);
            index = 1
        } else if index == 1 {
            reg = reg | ((*val as u32) << 8);
            index = 2
        } else if index == 2 {
            reg = reg | (*val as u32);
            index = 0;
            s.push(base64[((reg >> 18) & (0x3f)) as usize] as char);
            s.push(base64[((reg >> 12) & (0x3f)) as usize] as char);
            s.push(base64[((reg >> 6) & (0x3f)) as usize] as char);
            s.push(base64[(reg & (0x3f)) as usize] as char);
            reg = 0
        }
    }

    if index == 1 {
        s.push(base64[((reg >> 18) & (0x3f)) as usize] as char);
        s.push(base64[((reg >> 12) & (0x3f)) as usize] as char);
        s.push('=');
        s.push('=');
    } else if index == 2 {
        s.push(base64[((reg >> 18) & (0x3f)) as usize] as char);
        s.push(base64[((reg >> 12) & (0x3f)) as usize] as char);
        s.push(base64[((reg >> 6) & (0x3f)) as usize] as char);
        s.push('=');
    }

    return s;
}

pub fn fixed_xor(v1: &[u8], v2: &[u8]) -> Vec<u8> {
    let mut v = Vec::new();
    v.reserve(v1.len());
    for i in 0..v1.len() {
        v.push(v1[i] ^ v2[i])
    }
    return v;
}

fn base64_reverse_lookup(c: char) -> u8 {
    if 'A' <= c && c <= 'Z' {
        return (c as u8) - ('A' as u8);
    } else if 'a' <= c && c <= 'z' {
        return (c as u8) - ('a' as u8) + 26;
    } else if '0' <= c && c <= '9' {
        return (c as u8) - ('0' as u8) + 52;
    } else if c == '+' {
        return 62;
    } else if c == '/' {
        return 63;
    }
    return 64;
}

pub fn base64_to_bytes(b64: String) -> Vec<u8> {
    let mut v = Vec::new();
    let mut index = 0;
    let mut reg: u32 = 0;
    let mut eq = 0;
    for ch in b64.chars() {
        if ch != '=' {
            let vl = base64_reverse_lookup(ch) as u32;
            if vl >= 64 {
                continue;
            }
            reg = ((reg << 6) as u32) | vl;
        } else {
            reg = reg << 6;
            eq += 1;
        }
        index += 1;
        if index == 4 {
            v.push(((reg >> 16) & 0xFF) as u8);
            if eq <= 1 {
                v.push(((reg >> 8) & 0xFF) as u8);
            }
            if eq == 0 {
                v.push((reg & 0xFF) as u8);
            }
            index = 0;
        }
    }
    while index != 4 {
        reg = reg << 6;
        index += 1;
    }
    return v;
}

pub fn rotation_key_xor(key: &Vec<u8>, plain: &Vec<u8>) -> Vec<u8> {
    let mut v = vec![0; plain.len()];
    for i in 0..plain.len() {
        v[i] = key[i % key.len()] ^ plain[i];
    }
    return v;
}

pub fn edit_distance(v1: &[u8], v2: &[u8]) -> usize {
    let mut ret: usize = 0;
    for i in 0..v1.len() {
        let tv = v1[i] ^ v2[i];
        for j in 0..8 {
            ret += ((tv >> j) & 1) as usize;
        }
    }
    return ret;
}

pub fn sentense_score(v: &Vec<u8>) -> f32 {
    // https://en.wikipedia.org/wiki/Letter_frequency
    let rank = vec![
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406,
        6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074,
        0., 0.,
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
        } else if val_char == '\n' || val_char == ' ' || val_char == '\r' {
            total += 1.;
        } else if *val > 0 && (*val < 10 || *val > 126) {
            return -1.;
        } else {
            new_val = 27;
            total += 1.;
        }
        let c = count.entry(new_val).or_insert(0);
        *c += 1
    }

    for (k, v) in &count {
        result += ((*v as f32) / total) * rank[*k as usize];
    }

    return result;
}
