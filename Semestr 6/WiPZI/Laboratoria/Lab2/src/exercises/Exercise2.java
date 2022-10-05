package exercises;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.optimaize.langdetect.LanguageDetector;
import org.apache.tika.Tika;
import org.apache.tika.config.TikaConfig;
import org.apache.tika.detect.Detector;
import org.apache.tika.exception.TikaException;
import org.apache.tika.io.TikaInputStream;
import org.apache.tika.langdetect.OptimaizeLangDetector;
import org.apache.tika.language.LanguageIdentifier;
import org.apache.tika.metadata.Metadata;
import org.apache.tika.mime.MediaType;
import org.apache.tika.mime.MimeType;
import org.apache.tika.parser.AutoDetectParser;
import org.apache.tika.sax.BodyContentHandler;
import org.xml.sax.SAXException;

public class Exercise2
{

    private static final String DATE_FORMAT = "yyyy-MM-dd";
    private OptimaizeLangDetector langDetector;

    public static void main(String[] args)
    {
        Exercise2 exercise = new Exercise2();
        exercise.run();
    }

    private void run()
    {
        try
        {
            if (!new File("./outputDocuments").exists())
            {
                Files.createDirectory(Paths.get("./outputDocuments"));
            }

            initLangDetector();

            File directory = new File("./documents");
            File[] files = directory.listFiles();
            for (File file : files)
            {
                processFile(file);
            }
        } catch (IOException | SAXException | TikaException e)
        {
            e.printStackTrace();
        }

    }

    private void initLangDetector() throws IOException
    {
        // TODO initialize language detector (langDetector)
    }

    private void processFile(File file) throws IOException, SAXException, TikaException
    {
        AutoDetectParser parser = new AutoDetectParser();
        Metadata metadata = new Metadata();
        BodyContentHandler handler = new BodyContentHandler(-1);
        FileInputStream inputStream = new FileInputStream(file);

        TikaInputStream tikaInputStream = TikaInputStream.get(file);
        TikaConfig tikaConfig = TikaConfig.getDefaultConfig();
        Detector detector = tikaConfig.getDetector();
        String mediaType = detector.detect(tikaInputStream, metadata).toString();


        parser.parse(inputStream, handler, metadata);
        String[] metadataNames = metadata.names();
        String creatorName = null;
        String creationDate = null;
        String lastModification = null;
        String mimeType = mediaType;
        String content = handler.toString();

        LanguageIdentifier languageIdentifier = new LanguageIdentifier(content);
        String language = languageIdentifier.getLanguage();


        for(String name: metadataNames) {
//            System.out.println(name + ": " + metadata.get(name));
            switch (name) {
                case "creator": creatorName = metadata.get(name); break;
                case "Creation-Date": creationDate = metadata.get(name); break;
                case "Last-Modified": lastModification = metadata.get(name); break;
            }
        }

        saveResult(file.getName(), language, creatorName, creationDate, lastModification, mimeType, content); //TODO: fill with proper values
    }

    private void saveResult(String fileName, String language, String creatorName, String creationDate,
                            String lastModification, String mimeType, String content)
    {

        SimpleDateFormat dateFormat = new SimpleDateFormat(DATE_FORMAT);
        int index = fileName.lastIndexOf(".");
        String outName = fileName.substring(0, index) + ".txt";
        try
        {
            PrintWriter printWriter = new PrintWriter("./outputDocuments/" + outName);
            printWriter.write("Name: " + fileName + "\n");
            printWriter.write("Language: " + (language != null ? language : "") + "\n");
            printWriter.write("Creator: " + (creatorName != null ? creatorName : "") + "\n");
//            String creationDateStr = creationDate == null ? "" : dateFormat.format(creationDate);
            printWriter.write("Creation date: " + creationDate + "\n");
//            String lastModificationStr = lastModification == null ? "" : dateFormat.format(lastModification);
            printWriter.write("Last modification: " + lastModification + "\n");
            printWriter.write("MIME type: " + (mimeType != null ? mimeType : "") + "\n");
            printWriter.write("\n");
            printWriter.write(content + "\n");
            printWriter.close();
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }

}

