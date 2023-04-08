//
// Created by Atin Sakkeer Hussain on 02/03/2023.
//

#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H

#include <map>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Utilities.h"

using namespace std;

/*
 * The Result Table encapsulates the result of the evaluation of a clause.
 */
class ResultTable {
    vector<string> columns;
    unordered_map<string, vector<string>> table;

public:
    /**
     * Constructor for a ResultTable, using an initializer list of column-value pairs.
     *
     * @param args an initializer list of pairs representing the column names and their values.
     */
    ResultTable(initializer_list<pair<string, vector<string>>> args);

    /**
     * Constructor for a ResultTable, using an unordered map of column names and their corresponding values.
     *
     * @param table the unordered map of column names and their corresponding values.
     */
    explicit ResultTable(const unordered_map<string, vector<string>>& table);

    /**
     * Constructor for a ResultTable, using an unordered map of column names and their corresponding values, and a vector of column names.
     *
     * @param table the unordered map of column names and their corresponding values.
     * @param columns the vector of column names.
     */
    explicit ResultTable(const unordered_map<string, vector<string>>& table, vector<string> columns);

    /**
     * Returns the size of the ResultTable, i.e. the number of rows.
     *
     * @return the size of the ResultTable.
     */
    ::size_t getSize() const;

    /**
     * Returns a new ResultTable that is the intersection of the current ResultTable and the input ResultTable.
     *
     * @param table2 the input ResultTable to intersect with.
     * @return a new ResultTable that is the intersection of the current ResultTable and the input ResultTable.
     */
    ResultTable* intersection(ResultTable* table2);

    /**
     * Returns a new ResultTable that is the intersection of a vector of ResultTables.
     *
     * @param resultTables the vector of ResultTables to intersect.
     * @return a new ResultTable that is the intersection of a vector of ResultTables.
     */
    static ResultTable* intersection(vector<ResultTable*> resultTables);

    /**
     * Removes a column from the ResultTable.
     *
     * @param column the name of the column to remove.
     * @return a new ResultTable without the specified column.
     */
    ResultTable* removeColumn(string column) {
        auto it = this->table.find(column);
        if (it != this->table.end()) {
            this->table.erase(it);
        }
        return new ResultTable(this->table);
    }

    string toString() const;

    /**
     * Returns a new ResultTable with only the specified columns.
     *
     * @param columns the vector of column names to keep.
     * @return a new ResultTable with only the specified columns.
     */
    ResultTable* getColumns(const vector<string>& columns);

    /**
     * Returns the values of the ResultTable.
     *
     * @return a vector of strings representing the values of the ResultTable.
     */
    virtual vector<string> getValues();

    /**
      * Returns the values of a specified column in the ResultTable.
      *
      * @param column the name of the column to get the values from.
      * @return a vector of strings representing the values of the specified column in the ResultTable.
      */
    vector<string> getValues(const string& column);

    /**
     * Returns the names of the columns in the ResultTable.
     *
     * @return a vector of strings representing the names of the columns in the ResultTable.
     */
    vector<string> getColumnNames();

    /**
     * Renames a column with a new name
     *
     * @param oldName the old column name
     * @param newName the new column name
     */
    void renameColumn(const string& oldName, const string& newName);

    /**
     * Checks if two tables are equal
     *
     * @param table2 a ResultTable object
     *
     * @return a boolean value, true if tables are equal, false otherwise
     */
    bool equals(ResultTable* table2);

private:
    /**
     * Returns a cross product of two tables
     *
     * @param table2 a ResultTable object
     * @param all_keys an unordered set of all column names in both tables
     *
     * @return a ResultTable object representing the cross product of the two tables
     */
    ResultTable* crossProduct(ResultTable* table2, const unordered_set<string>& all_keys);

    /**
     * Returns a natural join of two tables
     *
     * @param table2 a ResultTable object
     * @param all_keys an unordered set of all column names in both tables
     * @param common_keys an unordered set of column names that are common to both tables
     *
     * @return a ResultTable object representing the natural join of the two tables
     */
    ResultTable* naturalJoin(ResultTable* table2, const unordered_set<string>& all_keys, unordered_set<string> common_keys);

};

class BooleanTrueTable : public ResultTable {
public:
    /**
     * Constructor for a boolean true table
     */
    BooleanTrueTable();

    /**
     * Returns a vector of string containing a single "true" value
     *
     * @return a vector of string containing a single "true" value
     */
    vector<string> getValues();
};

class BooleanFalseTable : public ResultTable {
public:
    /**
     * Constructor for a boolean false table
     */
    BooleanFalseTable();

    /**
     * Returns a vector of string containing a single "false" value
     *
     * @return a vector of string containing a single "false" value
     */
    vector<string> getValues();
};

#endif //SPA_RESULTTABLE_H
