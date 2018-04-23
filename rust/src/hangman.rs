use std::io::{Write, BufRead};

/** Public Functions **/
pub fn start_game(random_word: String) {
    //Starts the game and prints a message based on the result
    if play_game(&random_word, 10) {
        println!("Congratulations, you guessed the word \"{}\" correctly.\n", random_word);
    } else {
        println!("You did not guess \"{}\" correctly, and have been hanged.\n", random_word);
    }
}

/** Private Functions **/
fn play_game(random_word: &str, tries_total: u8) -> bool {
    let mut tries_left = tries_total;
    let mut guessed_chars = String::new();
    let rwl = random_word.len();
    let mut user_guess = (0..rwl).map(|_| "_").collect::<String>();

    while tries_left > 0 {
        let guess = get_guess_from_user();
        let incorrect_guess = update_user_guess(random_word, &mut user_guess, guess);
        let new_char = update_guessed_chars(&mut guessed_chars, guess);

        if incorrect_guess && new_char {
            tries_left -= 1;
        }

        if user_guess == random_word {
            return true;
        }
        print_status(tries_left, &user_guess, &guessed_chars);
    }
    false
}

fn update_user_guess(random_word: &str, user_guess: &mut String, guess: char) -> bool {
    let chars: Vec<(char, char)> = random_word.chars().zip(user_guess.chars()).collect();
    user_guess.clear();
    let mut incorrect_guess = true;
    for (r, g) in chars {
        if r == guess {
            user_guess.push(r);
            incorrect_guess = false;
        } else {
            user_guess.push(g);
        }
    }
    incorrect_guess
}


fn update_guessed_chars(guessed_chars: &mut String, guess: char) -> bool {
    if ! guessed_chars.contains(guess) {
        guessed_chars.push(guess);
        guessed_chars.push(' ');
        true
    } else {
        false
    }
}


fn get_guess_from_user() -> char {
    let mut buffer = String::new();
    loop {
        print!("Please enter your next guess: ");
        ::std::io::stdout().flush().ok().expect("flush stdout error");
        let handle = ::std::io::stdin();
        let guess = handle.lock().read_line(&mut buffer).expect("read error");

        //Simple hack as the newline always will be included with a char
        if guess > 1 {
            return buffer.chars().next().unwrap().to_ascii_lowercase();
        }
        buffer.clear();
    }
}

fn print_status(guesses_left: u8, current_guess: &str, guessed_chars: &str) {
    println!("Word: {}", current_guess);
    println!("Tries Left: {}", guesses_left);
    println!("Guessed Letters: {}\n", guessed_chars);

    println!("The Gallow\n");

    match guesses_left {
        10 => println!("\n\n\n\n\n\n\n"),
         9 => println!("\n\n\n\n\n   \n_______________\n\n"),
         8 => println!("\n\n\n  |\n  |\n  |\n________________\n\n"),
         7 => println!("  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"),
         6 => println!("  |--         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"),
         5 => println!("  |------         \n  |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"),
         4 => println!("  |------         \n  |     |\n  |\n  |\n  |\n  |\n  |\n________________\n\n"),
         3 => println!("  |------         \n  |     |\n  |     0\n  |\n  |\n  |\n  |\n________________\n\n"),
         2 => println!("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |\n  |\n  |\n________________\n\n"),
         1 => println!("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |\n  |\n________________\n\n"),
         _ => println!("  |------         \n  |     |\n  |     0\n  |    /|\\\n  |     |\n  |    / \\\n  |\n________________\n\n")
    }
}