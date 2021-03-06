# dbfexport

Export a dbf to a csv

**Support**

* FoxBASE+/Dbase III plus, no memo

**Requirements**

* gcc compiler

**Build**

```console
cd dbfexport
./build
```


**Examples**

```console
dbfexport /home/user/data/table.dbf >> table.csv
```

```console
dbfexport /home/user/data/table.dbf --fields "COL1 COL2 COL1 COL3 COL1" >> table.csv
```

```console
dbfexport /home/user/data/table.dbf --append -out table.csv
```

```console
dbfexport /home/user/data/table.dbf --separator "|" -out table.csv
```

```console
dbfexport /home/user/data/table.dbf --separator "|" > table.csv
```

```console
dbfexport /home/user/data/table.dbf --separator "|" --limit 10  -out table.csv
```

```console
dbfexport /home/user/data/table.dbf --separator "\t" --limit 10 --offset 200 -out table.csv
```

```console
dbfexport /home/user/data/table.dbf --separator ";" --limit 10 --offset 200 --encoding cp1252 -out table.csv
```
