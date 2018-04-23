extern crate rand;

use std;
use std::io::BufReader;
use std::io::BufRead;

use self::rand::Rng;

/** Public Functions **/
pub fn get_random_word(file_path: &str) -> String {
    //Only continue execution if the file exists
    let file_handle = std::fs::File::open(file_path);
    let file_handle = match file_handle {
        Ok(file) => file,
        Err(_) => {
            eprintln!("ERROR: the word list does not exist");
            std::process::abort()
        }
    };

    //Return a random line from the word list file
    let mut counter = 0;
    let random_index = get_random_index(file_path);
    let file_lines = BufReader::new(file_handle).lines();
    for line in file_lines {
        if counter == random_index {
            return line.unwrap().to_ascii_lowercase();
            //return Box::new(lowercase);
        }
        counter += 1;

    }
    eprintln!("ERROR: attempted to retrieve a word outside the word list");
    std::process::abort()
}

/** Private Functions **/
fn get_random_index(file_path: &str) -> i32 {
    let file_handle = std::fs::File::open(file_path).unwrap();
    let counted_lines = BufReader::new(file_handle).lines().count();
    let mut rng = rand::thread_rng();
    rng.gen_range(0, counted_lines as i32)
}