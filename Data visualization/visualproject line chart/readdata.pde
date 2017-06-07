class readdata {
  int rowcount;
  int columncount;
  float[][] data;
  String[] rowname;
  String[] columnname;
  
  
  readdata(String filename) {
    String[] row=loadStrings(filename);
    String[] column=split(row[0], ',');
    columnname = subset(column, 1); 
    scrubQuotes(columnname);
    columncount = columnname.length;

    rowname = new String[row.length-1];
    data = new float[row.length-1][];
    for (int i = 1; i < row.length; i++) {
      if (trim(row[i]).length() == 0) {
        continue; 
      }
      if (row[i].startsWith("#")) {
        continue;  
      }

  
      String[] pieces = split(row[i], ',');
      scrubQuotes(pieces);
      
   
      rowname[rowcount] = pieces[0];
      data[rowcount] = parseFloat(subset(pieces, 1));
      rowcount++;      
    }
    data = (float[][]) subset(data, 0, rowcount);
  }
  
  
  void scrubQuotes(String[] array) {
    for (int i = 0; i < array.length; i++) {
      if (array[i].length() > 2) {
        if (array[i].startsWith("\"") && array[i].endsWith("\"")) {
          array[i] = array[i].substring(1, array[i].length() - 1);
        }
      }
      array[i] = array[i].replaceAll("\"\"", "\"");
    }
  }
  
  
  int getRowCount() {
    return rowcount;
  }
  
  
  String getRowName(int rowIndex) {
    return rowname[rowIndex];
  }
  
  
  String[] getRowNames() {
    return rowname;
  }

  int getRowIndex(String name) {
    for (int i = 0; i < rowcount; i++) {
      if (rowname[i].equals(name)) {
        return i;
      }
    }
    return -1;
  }
  
 
  int getColumnCount() {
    return columncount;
  }
  
  
  String getColumnName(int colIndex) {
    return columnname[colIndex];
  }
  
  
  String[] getColumnNames() {
    return columnname;
  }


  float getFloat(int rowIndex, int col) {
   
    if ((rowIndex < 0) || (rowIndex >= data.length)) {
      throw new RuntimeException("There is no row " + rowIndex);
    }
    if ((col < 0) || (col >= data[rowIndex].length)) {
      throw new RuntimeException("Row " + rowIndex + " does not have a column " + col);
    }
    
    return data[rowIndex][col];
  }
  
  
  boolean isValid(int row, int col) {
    if (row < 0) return false;
    if (row >= rowcount) return false;

    if (col >= data[row].length) return false;
    if (col < 0) return false;
    return !Float.isNaN(data[row][col]);
  }


  float getColumnMin(int col) {
    float m = Float.MAX_VALUE;
    for (int row = 0; row < rowcount; row++) {
      if (isValid(row, col)) {
        if (data[row][col] < m) {
          m = data[row][col];
        }
      }
    }
    return m;
  }


  float getColumnMax(int col) {
    float m = -Float.MAX_VALUE;
    for (int row = 0; row < rowcount; row++) {
      if (isValid(row, col)) {
        if (data[row][col] > m) {
          m = data[row][col];
        }
      }
    }
    return m;
  }

  
  float getRowMin(int row) {
    float m = Float.MAX_VALUE;
    for (int col = 0; col < columncount; col++) {
      if (isValid(row, col)) {
        if (data[row][col] < m) {
          m = data[row][col];
        }
      }
    }
    return m;
  } 


  float getRowMax(int row) {
    float m = -Float.MAX_VALUE;
    for (int col = 0; col < columncount; col++) {
      if (isValid(row, col)) {
        if (data[row][col] > m) {
          m = data[row][col];
        }
      }
    }
    return m;
  }


  float getTableMin() {
    float m = Float.MAX_VALUE;
    for (int row = 0; row < rowcount; row++) {
      for (int col = 0; col < columncount; col++) {
        if (isValid(row, col)) {
          if (data[row][col] < m) {
            m = data[row][col];
          }
        }
      }
    }
    return m;
  }


  float getTableMax() {
    float m = -Float.MAX_VALUE;
    for (int row = 0; row < rowcount; row++) {
      for (int col = 0; col < columncount; col++) {
        if (isValid(row, col)) {
          if (data[row][col] > m) {
            m = data[row][col];
          }
        }
      }
    }
    return m;
  }

}


