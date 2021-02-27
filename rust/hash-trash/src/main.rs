use colored::*;
use rand::Rng;
use std::cmp::min;

static ARR_LEN: usize = 10;
static HASH_BITS: u64 = 256;
static BASE_SIMPLE: u64 = 251;
static UP_POW: u32 = 20;

fn get_hash(x: &u64) -> u64 {
    let mut powered: u64 = 1;
    for _ in 0..*x {
        powered *= BASE_SIMPLE;
    }
    powered % HASH_BITS
}

fn highlight_diff(lhs: &String, rhs: &String) -> String {
    let mut result = String::from("");

    for i in 0..min(lhs.len(), rhs.len()) {
        result += &if lhs.chars().nth(i).unwrap() == rhs.chars().nth(i).unwrap() {
            lhs.chars().nth(i).unwrap().to_string()
        } else {
            String::from(lhs.chars().nth(i).unwrap().to_string())
                .red()
                .to_string()
        };
    }

    result
}

fn main() {
    // ====================================================

    let mut x: Vec<u64> = Vec::new();
    let mut y: Vec<u64> = Vec::new();

    let mut rng = rand::thread_rng();
    for i in 0..ARR_LEN {
        x.push(rng.gen_range(0..u64::pow(2, UP_POW)));
        y.push(x[i] ^ 1 << rng.gen_range(1..10));
    }

    // ====================================================

    let mut bins_x: Vec<String> = Vec::new();
    let mut bins_y: Vec<String> = Vec::new();

    let mut hash_x: Vec<u64> = Vec::new();
    let mut hash_y: Vec<u64> = Vec::new();

    for i in 0..ARR_LEN {
        bins_x.push(format!("{:01$b}", x[i], UP_POW as usize));
        bins_y.push(format!("{:01$b}", y[i], UP_POW as usize));

        hash_x.push(get_hash(&x[i]));
        hash_y.push(get_hash(&y[i]));
    }

    // ====================================================

    println!("X:");
    for i in 0..ARR_LEN {
        println!(
            "\t{}\t\t{}\t\tH(x): {:10}",
            x[i],
            highlight_diff(&bins_x[i], &bins_y[i]),
            hash_x[i]
        );
    }

    println!("Y:");
    for i in 0..ARR_LEN {
        println!(
            "\t{}\t\t{}\t\tH(y): {:10}\tH(x) = H(y): {}",
            y[i],
            highlight_diff(&bins_y[i], &bins_x[i]),
            hash_y[i],
            hash_x[i] == hash_y[i]
        );
    }
}
