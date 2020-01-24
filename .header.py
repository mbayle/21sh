import os
import re

################################################################################
### List all the different type that functions can return in a regexp format
### Edit it carefully
################################################################################
format = "^(void|int|char|t_*|unsigned int|unsigned long|pid_t|size_t|long)"

################################################################################
### Activate or not recursive look for files in given directory
################################################################################
recursive_discover = True

################################################################################
### If some advanced files cause recurrent problems you shall ignore it and add
### prototypes manually hin header, before separator
### Example : ignored_files = [ "main.c", "file.c" ]
################################################################################
ignored_files = []

################################################################################
### Activate or unactivate verbose mode.
### You can define verbose level between 1 and 3.
################################################################################
verbose = 1

################################################################################
### Check file described by its name and its path is a valid code file.
### If it is this file can be read and parsed
################################################################################
def is_valid_filename(filename, filepath, recursive_discover):
    if (filename in ignored_files):
        return (False)
    elif (os.path.isdir(filepath)):
        if (recursive_discover):
            return (True)
        return (False)
    elif (not os.path.isfile(filepath)):
        return (False)
    elif (filename[0] == '.' or filename[-2:] != ".c"):
        return (False)
    return (True)

################################################################################
### List all files in a given directory.
### Discover can be recursive if recursive_discover is True
################################################################################
def read_dir(dir_path, files, recursive_discover):
    for filename in os.listdir(dir_path):
        filepath = os.path.join(dir_path, filename)
        if (not is_valid_filename(filename, filepath, recursive_discover)):
            continue
        if (recursive_discover and os.path.isdir(filepath)):
            read_dir(filepath, files, recursive_discover)
            continue
        files.append({'filename' : filename, 'filepath' : filepath})
    return sorted(files, key = lambda i: (i['filename']))

################################################################################
### Read files and parse it using regexp.
###	files is a list of dictionnaries containing two keys : filename and filepath
###	Return a dictionnary containing list of dictionnaries.
###	Each key is a filename, associated to a list of dictionnaries representing prototypes.
###  contain 'type' and 'name' keys. 'type' returned type of the functions
################################################################################
def parse_files(files):
    res = {}
    for file in files:
        if (verbose >= 2): print("parsing : %s" % file['filepath'])
        fdr = open(file['filepath'])
        content = []
        line = fdr.readline()
        while (line):
            if (re.search(format, line) != None):
                prototype = line.rstrip()
                if (verbose >= 2): print("\t" + prototype)
                while (line and prototype[-1] != ")"):
                    line = fdr.readline()
                    line = line.strip()
                    prototype += " " + line
                prototype = prototype.replace('    ', '\t')
                prototype = prototype.split('\t')
                prototype = [i for i in prototype if (i != "")]
                buffer = {"type" : prototype[0], "name" : prototype[1]}
                content.append(buffer)
            line = fdr.readline()
        res[file['filename']] = content
    return (res)

################################################################################
### format_dir_datas
###      create from formated string, ready to print in header, read_dir datas
###		Added condition to ignore global variable declaration than could create problems
###			Now any function starting by g_ is ignored, but a message is prompted.
################################################################################
def format_dir_datas(dir_data, tab_offset):
    res = ""
    max_tabs = tab_offset
    if (max_tabs == 0):
        max_tabs = 2
    ## Determine maximum number of tabs to add
    for file in dir_data:
        for function in dir_data[file]:
            length = len(function["type"])
            tabs = length // 4
            if (length % 4):
                tabs += 1
            if (tabs > max_tabs):
                max_tabs = tabs

    ## Create every file list of prototypes
    tabs = "\t" * max_tabs
    for file in dir_data:
        res += "/*\n** " + file + "\n*/\n"
        for function in dir_data[file]:
            str = function["type"]
            str += "\t" * (max_tabs - (len(function["type"]) // 4))
            if (function["name"][0] == "g" and function["name"][1] == '_'):
                if (verbose >=1): print("Global var declaration found and ignored : " + function["name"])
                continue ;
            str += function["name"]
            str += ";\n"
            if (len(str) + 3 * max_tabs >= 80):
                str = function["type"]
                str += "\t" * (max_tabs - (len(function["type"]) // 4))
                str += function["name"].split("(", 1)[0]
                str += "(\n\t"
                # str += function["name"].split("(", 1)[1].strip()
                buff = function["name"].split("(", 1)[1].strip()
                if (len(buff) + 3 * max_tabs >= 80):
                    for a in buff.split(","):
                        str += a.strip()
                        if (a.strip()[-1] == ')'):
                            str += ";\n"
                        else :
                            str += ",\n\t"
                else :
                    str += buff + ";\n"
            res += str
        res += "\n"
    return res

################################################################################
### Read header described by header_path. It store content that shall not be
###	modified, and delete the rest (everything after delimitor).
### It then add new content, well formated.
################################################################################
def create_header(header_path, datas):
    # Open header in reading mode
    fdr = open(header_path, 'r')
    header_content = ""
    line = fdr.readline()

    # Read file until header delimitation or end of file
    while (line != ""):
        header_content += line
        if (line.strip() == "*" * 80):
            header_content += "*/\n\n"
            break
        line = fdr.readline()

    # Add header delimitation if do not exists
    if (line == ""):
        header_content = header_content.replace('\n#endif\n', "")
        header_content += "/*\n"
        header_content += "*" * 80 + "\n"
        header_content += "*/\n\n"

    # Add datas to content
    header_content += datas
    header_content += "#endif\n"
    return header_content

def write_header(header, content):
    fdr = open(header, 'r')
    initial_content = fdr.read()
    fdr.close()
    if (initial_content == content):
        return
    fd_header = open(header, "w")
    fd_header.write(content)
    fd_header.close()
    if (verbose >= 1): print("Updated : " + header)

def automatic_header(dir_path, header_path, tab_offset=5, recursive_discover=True):
    if (not os.path.isdir(dir_path)):
        print("Cannot find :", dir_path)
        return
    elif (not os.path.isfile(header_path)):
        print("Cannot find :", header_path)
        return
    if (verbose >= 2):
        print("Launching : dir : " + dir_path + " || file : " + header_path)
    files = read_dir(dir_path, [], recursive_discover)
    dir_data = parse_files(files)
    res = format_dir_datas(dir_data, tab_offset)
    header_content = create_header(header_path, res)
    write_header(header_path, header_content)

################################################################################
### To add a new automatic task :
###     Add a call to automatic_header function as :
###     automatic_header("srcs dir paths", "header file path", tab_offset, recursive_discover=True)
###         srcs dir : where to look for .c files
###         header file :Which .h file you want to write in
###         tab_offset : change it if you have some norme troubles,
###                           5 is quite a good default value
###         recursive_discover : Activate if srcs task shall look into srcs dir
###                           subdirectories
################################################################################
automatic_header("./src/lexer", "./includes/lexer.h", tab_offset=5, recursive_discover=True)
automatic_header("./src/parser", "./includes/parser.h", tab_offset=5, recursive_discover=False)
automatic_header("./src/parser/grammar", "./includes/grammar.h", tab_offset=5, recursive_discover=False)
automatic_header("./src/ast", "./includes/mybtree.h", tab_offset=5, recursive_discover=True)
#automatic_header("./src", "./include/test.h", tab_offset=5, recursive_discover=True)
