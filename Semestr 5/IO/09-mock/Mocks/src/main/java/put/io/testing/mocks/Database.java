
        package put.io.testing.mocks;

import put.io.students.fancylibrary.database.IFancyDatabase;

import java.util.Collections;
import java.util.List;

public class Database implements IFancyDatabase {

    @Override
    public void connect() {
    }

    @Override
    public <T> void persist(T t) {

    }

    @Override
    public <T> List<T> queryAll() {

        return Collections.emptyList();
    }

    @Override
    public void close() {

    }
}