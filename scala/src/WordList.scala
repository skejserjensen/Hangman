import scala.util.Random
import scala.io.Source

class WordList(wordListPath: String) {
 
  /* Package Methods */
  def getRandomWord(): String = {
    val wordListSource = Source.fromFile(this.wordListPath)
    val randomWord = wordListSource.getLines.drop(this.getRandomIndex).next
    wordListSource.close
    randomWord
  }

  /* Private Methods */
  private def getRandomIndex(): Int = this.randomGenerator.nextInt(this.wordListLength)

  private def computeWordListSize(): Int = {
    //We save the size as a the file of a word list class cannot be changed
    val wordListSource = Source.fromFile(this.wordListPath)
    val listLength = wordListSource.getLines.size
    wordListSource.close
    listLength
  }

  /* Instance variables */
  private val randomGenerator: Random = new Random()
  private val wordListLength: Int = this.computeWordListSize()
}
