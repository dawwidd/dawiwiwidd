### LOAD THE DOCUMENTS (RAW STRINGS), YOU CAN SKIP IT
def loadDocuments(fileName):
    file = open(fileName,'r', encoding='utf-8-sig')
    documents = []
    document = []
    for line in file:
        if line == '\n': 
            documents.append(" ".join(document))
            document = []
        else: document.append(line)
    documents.append(" ".join(document))
    return documents

### SOME SIMPLE TEXT PROCESSING, YOU CAN IGNORE IT (TODO MOZE JAKAS BIBLIOTEKA???)
def suff(s, suff):
    if len(s) >= len(suff) and s[-len(suff):] == suff: return True
    return False

def getSingular(s):
    if suff(s, "ies"): return s[:-3] + "y"
    if suff(s, "rs") or suff(s, "ps") or suff(s, "es") or suff(s, "ts") or suff(s, "ns") or suff(s, "ms"):
        return s[:-1]
    return s
    
def validate(s):
    if len(s) < 3: return False
    if any(char.isdigit() for char in s): return False
    if "'" in s or "@" in s or "/" in s: return False
    return True

### GET TOKENS FROM A CONTENT (STRING)
def simpleTextProcessing(content, re):
    content = content.lower()
    content = re.sub('[.();,:|&\-\?\!\n\[\]\+\>\"]', '', content)
    tokens = [getSingular(s) for s in content.split(' ') if validate(s)]
    return tokens