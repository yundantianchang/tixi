import fileinput, sys
import os.path

def remove_text(filein, text):
    f = open(filein,'r')
    filedata = f.read()
    f.close()


    newdata = filedata.replace(text,"")

    f = open(filein,'w')
    f.write(newdata)
    f.close()

if __name__ == "__main__":
    assert(len(sys.argv) == 3)

    filename = sys.argv[1]
    text = sys.argv[2]

    text = text.replace("\\", "/")

    remove_text(filename, text)
    text = text[0].lower() + text[1:]
    remove_text(filename, text)