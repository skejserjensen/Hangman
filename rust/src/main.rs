mod word_list;
mod hangman;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let random_word = match args.len() {
        2 => word_list::get_random_word(&args[1]),
        _ => word_list::get_random_word("../data/wordlist")
    };
    hangman::start_game(random_word);
}