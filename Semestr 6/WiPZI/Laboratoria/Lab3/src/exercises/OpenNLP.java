package exercises;
import opennlp.tools.chunker.ChunkerME;
import opennlp.tools.chunker.ChunkerModel;
import opennlp.tools.langdetect.Language;
import opennlp.tools.langdetect.LanguageDetectorME;
import opennlp.tools.langdetect.LanguageDetectorModel;
import opennlp.tools.lemmatizer.DictionaryLemmatizer;
import opennlp.tools.namefind.NameFinderME;
import opennlp.tools.namefind.TokenNameFinderModel;
import opennlp.tools.postag.POSModel;
import opennlp.tools.postag.POSTaggerME;
import opennlp.tools.sentdetect.SentenceDetectorME;
import opennlp.tools.sentdetect.SentenceModel;
import opennlp.tools.stemmer.PorterStemmer;
import opennlp.tools.tokenize.TokenizerME;
import opennlp.tools.tokenize.TokenizerModel;
import opennlp.tools.util.Span;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class OpenNLP {

    public static String LANG_DETECT_MODEL = "models/langdetect-183.bin";
    public static String TOKENIZER_MODEL = "models/en-token.bin";
    public static String SENTENCE_MODEL = "models/en-sent.bin";
    public static String POS_MODEL = "models/en-pos-maxent.bin";
    public static String CHUNKER_MODEL = "models/en-chunker.bin";
    public static String LEMMATIZER_DICT = "models/en-lemmatizer.dict";
    public static String NAME_MODEL = "models/en-ner-person.bin";
    public static String ENTITY_XYZ_MODEL = "models/en-ner-xyz.bin";

	public static void main(String[] args) throws IOException
    {
		OpenNLP openNLP = new OpenNLP();
		openNLP.run();
	}

	public void run() throws IOException
    {

//		languageDetection();
//		 tokenization();
//         sentenceDetection();
//		 posTagging();
//		 lemmatization();
//		 stemming();
//		 chunking();
		 nameFinding();
	}

	private void languageDetection() throws IOException
    {
		File modelFile = new File(LANG_DETECT_MODEL);
		LanguageDetectorModel model = new LanguageDetectorModel(modelFile);

		LanguageDetectorME languageDetectorME = new LanguageDetectorME(model);

		String text = "";
//		text = "cats";
//		 text = "cats like milk";
//		 text = "Many cats like milk because in some ways it reminds them of their mother's milk.";
//		 text = "The two things are not really related. Many cats like milk because in some ways it reminds them of their mother's milk.";
		/*text = "The two things are not really related. Many cats like milk because in some ways it reminds them of their mother's milk. "
				+ "It is rich in fat and protein. They like the taste. They like the consistency . "
				+ "The issue as far as it being bad for them is the fact that cats often have difficulty digesting milk and so it may give them "
				+ "digestive upset like diarrhea, bloating and gas. After all, cow's milk is meant for baby calves, not cats. "
				+ "It is a fortunate quirk of nature that human digestive systems can also digest cow's milk. But humans and cats are not cows.";*/
//		 text = "Many cats like milk because in some ways it reminds them of their mother's milk. Le lait n'est pas forc�ment mauvais pour les chats";
		 text = "Many cats like milk because in some ways it reminds them of their mother's milk. Le lait n'est pas forc�ment mauvais pour les chats. "
		 + "Der Normalfall ist allerdings der, dass Salonl�wen Milch weder brauchen noch gut verdauen k�nnen.";

		Language textLanguage = languageDetectorME.predictLanguage(text);
		System.out.println(textLanguage.getLang() + " " + textLanguage.getConfidence());

	}

	private void tokenization() throws IOException
    {
		String text = "";
		File tokenizerFile = new File(TOKENIZER_MODEL);
		TokenizerModel model = new TokenizerModel(tokenizerFile);
		TokenizerME tokenizerME = new TokenizerME(model);

		text = "Since cats were venerated in ancient Egypt, they were commonly believed to have been domesticated there, "
				+ "but there may have been instances of domestication as early as the Neolithic from around 9500 years ago (7500 BC).";
		/*text = "Since cats were venerated in ancient Egypt, they were commonly believed to have been domesticated there, "
				+ "but there may have been instances of domestication as early as the Neolithic from around 9,500 years ago (7,500 BC).";
		text = "Since cats were venerated in ancient Egypt, they were commonly believed to have been domesticated there, "
		 + "but there may have been instances of domestication as early as the Neolithic from around 9 500 years ago ( 7 500 BC).";*/

		String[] tokenizedStrings = tokenizerME.tokenize(text);
		double[] tokenProbabilities = tokenizerME.getTokenProbabilities();

		for(String word: tokenizedStrings) {
			System.out.println(word + " ");
		}

		for(double prob: tokenProbabilities) {
			System.out.println(prob);
		}
	}

	private void sentenceDetection() throws IOException
    {
		File sentenceFile = new File(SENTENCE_MODEL);
		SentenceModel model = new SentenceModel(sentenceFile);
		SentenceDetectorME sentenceDetectorME = new SentenceDetectorME(model);

		String text = "";
		text = "Hi.";
//		text = "Hi. How are you? Welcome to OpenNLP. "
//				+ "We provide multiple built-in methods for Natural Language Processing.";
//		text = "Hi. How are you?! Welcome to OpenNLP? "
//				+ "We provide multiple built-in methods for Natural Language Processing.";
//		text = "Hi. How are you? Welcome to OpenNLP.?? "
//				+ "We provide multiple . built-in methods for Natural Language Processing.";
//		text = "The interrobang, also known as the interabang (often represented by ?! or !?), "
//				+ "is a nonstandard punctuation mark used in various written languages. "
//				+ "It is intended to combine the functions of the question mark (?), or interrogative point, "
//				+ "and the exclamation mark (!), or exclamation point, known in the jargon of printers and programmers as a \"bang\". ";

		String[] detectedSentences = sentenceDetectorME.sentDetect(text);
		double[] sentenceProbabilities = sentenceDetectorME.getSentenceProbabilities();

		for(String sentence: detectedSentences) {
			System.out.println(sentence + " ");
		}

		for(double prob: sentenceProbabilities) {
			System.out.println(prob);
		}
	}

	private void posTagging() throws IOException {
		File posFile = new File(POS_MODEL);
		POSModel model = new POSModel(posFile);
		POSTaggerME posTaggerME = new POSTaggerME(model);

		String[] sentence = new String[0];
//		sentence = new String[] { "Cats", "like", "milk" };
//		sentence = new String[]{"Cat", "is", "white", "like", "milk"};
//		sentence = new String[] { "Hi", "How", "are", "you", "Welcome", "to", "OpenNLP", "We", "provide", "multiple",
//				"built-in", "methods", "for", "Natural", "Language", "Processing" };
		sentence = new String[] { "She", "put", "the", "big", "knives", "on", "the", "table" };

		String[] posTags = posTaggerME.tag(sentence);

		for(String tag: posTags) {
			System.out.println(tag);
		}
	}

	private void lemmatization() throws IOException
    {
		File lemmaFile = new File(LEMMATIZER_DICT);
		DictionaryLemmatizer lemmatizer = new DictionaryLemmatizer(lemmaFile);

		String[] text = new String[0];
		text = new String[] { "Hi", "How", "are", "you", "Welcome", "to", "OpenNLP", "We", "provide", "multiple",
				"built-in", "methods", "for", "Natural", "Language", "Processing" };
		String[] tags = new String[0];
		tags = new String[] { "NNP", "WRB", "VBP", "PRP", "VB", "TO", "VB", "PRP", "VB", "JJ", "JJ", "NNS", "IN", "JJ",
				"NN", "VBG" };

		String[] lemmatizedTokens = lemmatizer.lemmatize(text, tags);

		for(String token: lemmatizedTokens) {
			System.out.println(token);
		}
	}

	private void stemming()
    {
		PorterStemmer stemmer = new PorterStemmer();
		String[] sentence = new String[0];
		sentence = new String[] { "Hi", "How", "are", "you", "Welcome", "to", "OpenNLP", "We", "provide", "multiple",
				"built-in", "methods", "for", "Natural", "Language", "Processing" };

		ArrayList<String> stemmedTokens = new ArrayList<>();

		for(String word: sentence) {
			String stem = stemmer.stem(word);
			stemmedTokens.add(stem);
		}

		for(String token: stemmedTokens) {
			System.out.println(token);
		}
	}
	
	private void chunking() throws IOException
    {
		File chunkerFile = new File(CHUNKER_MODEL);
		ChunkerModel model = new ChunkerModel(chunkerFile);
		ChunkerME chunkerME = new ChunkerME(model);

		String[] sentence = new String[0];
		sentence = new String[] { "She", "put", "the", "big", "knives", "on", "the", "table" };

		String[] tags = new String[0];
		tags = new String[] { "PRP", "VBD", "DT", "JJ", "NNS", "IN", "DT", "NN" };

		String[] chunks = chunkerME.chunk(sentence, tags);

		for(String chunk: chunks) {
			System.out.println(chunk);
		}
	}

	private void nameFinding() throws IOException
    {
		File nameFinderFile = new File(NAME_MODEL);
		TokenNameFinderModel nameFinderModel = new TokenNameFinderModel(nameFinderFile);
		NameFinderME nameFinderME = new NameFinderME(nameFinderModel);

		File entityFinderFile = new File(ENTITY_XYZ_MODEL);
		TokenNameFinderModel entityFinderModel = new TokenNameFinderModel(entityFinderFile);
		NameFinderME entityFinderME = new NameFinderME(entityFinderModel);

		File tokenizerFile = new File(TOKENIZER_MODEL);
		TokenizerModel tokenizerModel = new TokenizerModel(tokenizerFile);
		TokenizerME tokenizerME = new TokenizerME(tokenizerModel);

		String text = "he idea of using computers to search for relevant pieces of information was popularized in the article "
				+ "As We May Think by Vannevar Bush in 1945. It would appear that Bush was inspired by patents "
				+ "for a 'statistical machine' - filed by Emanuel Goldberg in the 1920s and '30s - that searched for documents stored on film. "
				+ "The first description of a computer searching for information was described by Holmstrom in 1948, "
				+ "detailing an early mention of the Univac computer. Automated information retrieval systems were introduced in the 1950s: "
				+ "one even featured in the 1957 romantic comedy, Desk Set. In the 1960s, the first large information retrieval research group "
				+ "was formed by Gerard Salton at Cornell. By the 1970s several different retrieval techniques had been shown to perform "
				+ "well on small text corpora such as the Cranfield collection (several thousand documents). Large-scale retrieval systems, "
				+ "such as the Lockheed Dialog system, came into use early in the 1970s.";

		String[] tokenizedText = tokenizerME.tokenize(text);

		Span[] names = nameFinderME.find(tokenizedText);
		Span[] entities = entityFinderME.find(tokenizedText);

		for(Span name: names) {
			System.out.println(name);
		}

		for(Span entity: entities) {
			System.out.println(entity);
		}
	}

}
