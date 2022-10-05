import org.apache.commons.io.FileUtils;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.*;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.tika.exception.TikaException;
import org.apache.tika.metadata.Metadata;
import org.apache.tika.parser.ParseContext;
import org.apache.tika.parser.html.HtmlParser;
import org.apache.tika.sax.BodyContentHandler;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;

import java.io.*;
import java.nio.file.Paths;
import java.util.ArrayList;

public class Indexer
{
    public static void main(String args[])
    {
        Indexer indexer = new Indexer();
        indexer.indexDocuments();
    }

    private void indexDocuments()
    {
        try
        {
            FileUtils.deleteDirectory(new File(Constants.index_dir));
        } catch (IOException ignored)
        {
        }

        ArrayList<Document> documents = getHTMLDocuments();

        StandardAnalyzer standardAnalyzer = new StandardAnalyzer();
        IndexWriterConfig indexWriterConfig = new IndexWriterConfig();
        Directory directory = null;

        try {
            directory = FSDirectory.open(Paths.get(Constants.index_dir));
            IndexWriter indexWriter = new IndexWriter(directory, indexWriterConfig);

            for(Document document: documents) {
                indexWriter.addDocument(document);
            }

            indexWriter.commit();
            indexWriter.close();
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


    private ArrayList<Document> getHTMLDocuments()
    {
        // This method is finished. Find getHTMLDocument
        File dir = new File("pages");
        File[] files = dir.listFiles();
        if (files != null)
        {
            ArrayList<Document> htmls = new ArrayList<>(files.length);
            for (int id = 0; id < files.length; id++)
            {
                System.out.println("Loading "+ files[id].getName());
                // TODO finish getHTML document
                htmls.add(getHTMLDocument("pages/" + files[id].getName(), id));
            }
            return htmls;
        }
        return null;
    }

    private Document getHTMLDocument(String path, int id)
    {
        File file = new File(path);
        Document document = new Document();

        StoredField storedField = new StoredField(Constants.id, id);
        TextField textField = new TextField(Constants.content, getTextFromHTMLFile(file), Field.Store.NO);
        StringField stringField = new StringField(Constants.filename, file.getName(), Field.Store.YES);
        IntPoint intPoint = new IntPoint(Constants.filesize, ((int) file.length()));
        StoredField storedFieldSize = new StoredField(Constants.filesize_int, ((int) file.length()));

        document.add(storedField);
        document.add(textField);
        document.add(stringField);
        document.add(intPoint);
        document.add(storedFieldSize);

        return document;
    }

    // (DONE)
    private String getTextFromHTMLFile(File file)
    {
        BodyContentHandler handler = new BodyContentHandler();
        Metadata metadata = new Metadata();
        FileInputStream inputStream;
        try
        {
            inputStream = new FileInputStream(file);
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
            return null;
        }

        ParseContext pContext = new ParseContext();

        //Html parser
        HtmlParser htmlparser = new HtmlParser();
        try
        {
            htmlparser.parse(inputStream, handler, metadata, pContext);
        } catch (IOException | SAXException | TikaException e)
        {
            e.printStackTrace();
        }

        return handler.toString();
    }

}
