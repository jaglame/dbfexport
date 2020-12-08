"""
8859-1 -> latin-1
8859-15 -> latin-9
http://www.ltg.ed.ac.uk/~richard/utf-8.cgi?input=%C3%BB&mode=char


cp1252: windows
cp437: ibm -> https://www.ascii-codes.com/

"""

chars = "¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ€"

def generate_chars(coding="cp1252"):

    for c in chars:
        try:
            c2 = c.encode(coding)
            c3 = c.encode()
            x1 = str(c2).replace("b'", "'", 1)
            x2 = str(c3).replace("b'", "'", 1).replace("'", '"')
            print(f"else if(c == {x1})")
            print(f"    p = {x2}; // {c}")
        except UnicodeEncodeError as e:
            pass

    print("else if ((unsigned char)c > 127)")
    print("    c = '?'; // unknow")


def generate_test(coding="cp1252"):
    """ """
    l = []
    for c in chars:
        try:
            c2 = c.encode(coding)
            x1 = str(c2).replace("b'", "'", 1).replace("'", "")
            l.append(x1)
        except UnicodeEncodeError as e:
            pass

    out = "".join(l)
    print(f'char * text = "{out}";')


if __name__ == "__main__":
    """ """
    generate_chars("cp437")
    generate_test("cp437")










