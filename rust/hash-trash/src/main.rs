use colored::*;
use rand::Rng;
use std::cmp::min;

static ARR_LEN: usize = 10;
static HASH_BITS: u64 = 256;
static BASE_SIMPLE: u64 = 251;
static UP_POW: u32 = 32; // max 32

fn get_hash(x: &u64) -> u64 {
    u64::pow(BASE_SIMPLE, *x as u32) % HASH_BITS
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

fn get_correlatio_coeff(lhs: &Vec<u64>, rhs: &Vec<u64>) -> f64 {
    let length = min(lhs.len(), rhs.len());
    let mut avg_x = 0.;
    let mut avg_y = 0.;
    let mut avg_x2 = 0.;
    let mut avg_y2 = 0.;

    for i in 0..length {
        avg_x += lhs[i] as f64;
        avg_y += rhs[i] as f64;
        avg_x2 += (lhs[i] * lhs[i]) as f64;
        avg_y2 += (rhs[i] * rhs[i]) as f64;
    }

    avg_x /= length as f64;
    avg_y /= length as f64;
    avg_x2 /= length as f64;
    avg_y2 /= length as f64;

    let delta_x2 = avg_x2 - avg_x * avg_x;
    let delta_y2 = avg_y2 - avg_y * avg_y;
    let delta_x = delta_x2.sqrt();
    let delta_y = delta_y2.sqrt();
    let mut numerator = 0.;

    for i in 0..length {
        numerator += (lhs[i] as f64 - avg_x) * (rhs[i] as f64 - avg_y);
    }

    let denominator = length as f64 * delta_x * delta_y;

    numerator / denominator
}

fn main() {
    // ====================================================

    let mut x: Vec<u64> = Vec::new();
    let mut y: Vec<u64> = Vec::new();

    let mut rng = rand::thread_rng();
    for i in 0..ARR_LEN {
        x.push(rng.gen_range(0..u64::pow(2, UP_POW)));
        y.push(x[i] ^ 1 << i);
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

    // ====================================================

    println!(
        "Correlation coefficient (X, H(X)):\t{}",
        get_correlatio_coeff(&x, &hash_x)
    );
    println!(
        "Correlation coefficient (Y, H(Y)):\t{}",
        get_correlatio_coeff(&y, &hash_y)
    );
    println!(
        "Correlation coefficient (H(X), H(Y)):\t{}",
        get_correlatio_coeff(&hash_x, &hash_y)
    );
    println!(
        "Correlation coefficient (X, Y):\t{}",
        get_correlatio_coeff(&x, &y)
    );
}
