object Main {
  def main(args: Array[String]) {
    if(args.size == 1) {
      val hangman = new Hangman(args(0))
      hangman.startGame()
    }
    else {
      val hangman = new Hangman("../data/wordlist")
      hangman.startGame()
    }
  }
}
