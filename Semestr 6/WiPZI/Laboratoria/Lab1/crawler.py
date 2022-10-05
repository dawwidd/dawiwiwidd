# Author: Michal Tomczyk
# michal.tomczyk@cs.put.poznan.pl
# Poznan University of Technology
# Institute of Computing Science
# Laboratory of Intelligent Decision Support Systems
import urllib.request as req
import sys
import os
from copy import deepcopy
from html.parser import HTMLParser

      
class Parser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.output_list = []
    
    def handle_starttag(self, tag, attrs):
        if tag == 'a':
            self.output_list.append(dict(attrs).get('href'))


class Dummy_Policy:
    def getURL(self, c, iteration):
        if len(c.URLs) == 0:
            return None
        else:
            return c.seedURLs[0]
            
    def updateURLs(self, c, retrievedURLs, retrievedURLsWD, iteration):
        pass


class LIFO_Policy:
    def __init__(self, c):
        self.queue = deepcopy(c.seedURLs)

    def getURL(self, c, iteration):
        if len(self.queue) == 0:
            self.queue = deepcopy(c.seedURLs)
            return self.queue.pop()
        else:
            url = self.queue.pop()
            return url
            
            
    def updateURLs(self, c, retrievedURLs, retrievedURLsWD, iteration):
        tmpList = list(deepcopy(retrievedURLs))
        tmpList.sort(key=lambda url: url[len(url) - url[::-1].index('/'):])

        for url in tmpList:
            self.queue.append(url)


class LIFO_Cycle_Policy:
    def __init__(self, c):
        self.queue = deepcopy(c.seedURLs)
        self.fetched = set()

    def getURL(self, c, iteration):
        if len(self.queue) == 0:
            self.queue = deepcopy(c.seedURLs)
            self.fetched.clear()

        while self.queue:
            url = self.queue.pop()
            if not url in self.fetched:
                self.fetched.add(url)
                return url
            if len(self.queue) == 0:
                self.queue = deepcopy(c.seedURLs)
                self.fetched.clear()
            
            
    def updateURLs(self, c, retrievedURLs, retrievedURLsWD, iteration):
        tmpList = list(deepcopy(retrievedURLs))
        tmpList.sort(key=lambda url: url[len(url) - url[::-1].index('/'):])

        for url in tmpList:
            self.queue.append(url)


# class LIFO_Authority_Policy:
#     def __init__(self, c):
#         self.queue = deepcopy(c.seedURLs)
#         self.fetched = set()

#     def getURL(self, c, iteration):
#         if len(self.queue) == 0:

#             self.queue = deepcopy(c.seedURLs)
#             self.fetched.clear()

#         while self.queue:
#             url = self.queue.pop()
#             if not url in self.fetched:
#                 self.fetched.add(url)
#                 return url
#             if len(self.queue) == 0:
#                 self.queue = deepcopy(c.seedURLs)
#                 self.fetched.clear()
            
            
#     def updateURLs(self, c, retrievedURLs, retrievedURLsWD, iteration):
#         tmpList = list(deepcopy(retrievedURLs))
#         tmpList.sort(key=lambda url: url[len(url) - url[::-1].index('/'):])

#         for url in tmpList:
#             self.queue.append(url)


class FIFO_Policy:
    def __init__(self, c):
        self.queue = deepcopy(c.seedURLs)

    def getURL(self, c, iteration):
        if len(self.queue) == 0:
            self.queue = list(deepcopy(c.seedURLs))
            return self.queue.pop(0)
        else:
            url = self.queue.pop(0)
            return url
            
            
    def updateURLs(self, c, retrievedURLs, retrievedURLsWD, iteration):
        tmpList = list(deepcopy(retrievedURLs))
        tmpList.sort(key=lambda url: url[len(url) - url[::-1].index('/'):])

        for url in tmpList:
            self.queue.append(url)
        
    
class Container:
    def __init__(self):
        self.crawlerName = "IRbot"
        # self.example = "exercise1"
        self.example = "exercise2"
        # self.example = "exercise3"

        self.rootPage = "http://www.cs.put.poznan.pl/mtomczyk/ir/lab1/" + self.example
        self.seedURLs = ["http://www.cs.put.poznan.pl/mtomczyk/ir/lab1/"
            + self.example + "/s0.html"]

        self.URLs = set([])
        self.outgoingURLs = {}
        self.incomingURLs = {}

        # self.generatePolicy = Dummy_Policy()
        # self.generatePolicy = LIFO_Policy(self)
        # self.generatePolicy = FIFO_Policy(self)
        self.generatePolicy = LIFO_Cycle_Policy(self)
        # self.generatePolicy = LIFO_Authority_Policy(self)


        self.toFetch = None
        self.iterations = 10

        self.storePages = True
        self.storeURLs = True

        self.storedPagesPath = "./" + self.example + "/pages/"
        self.storedURLsPath = "/" + self.example +"/urls/"

        self.storeOutgoingURLs = True
        self.storedOutgoingURLs = "/" + self.example + "/outgoing/"

        self.storeIncomingURLs = True
        self.storedIncomingURLs = "/" + self.example + "/incoming/"
        
        self.debug = False 
        

def main():

    c = Container()
    inject(c)
    
    for iteration in range(c.iterations):
    
        if c.debug: 
            print("=====================================================")
            print("Iteration = " + str(iteration + 1) )
            print("=====================================================")
        
        generate(c, iteration)
        if (c.toFetch == None):
            if c.debug:
                print("   No page to fetch!")
            continue
                
        page = fetch(c)
    
        if page == None:
            if c.debug:
                print("   Unexpected error; skipping this page")
            removeWrongURL(c)
            continue
            
        
        htmlData, retrievedURLs = parse(c, page, iteration)
        
        
        if c.storePages:
            storePage(c, htmlData)
        
       
        retrievedURLs = getNormalisedURLs(retrievedURLs)
        
        
        updateOutgoingURLs(c, retrievedURLs)
        updateIncomingURLs(c, retrievedURLs)
        
        
        retrievedURLs = getFilteredURLs(c, retrievedURLs)
        
        
        retrievedURLsWD = removeDuplicates(c, retrievedURLs)
        
        
        c.generatePolicy.updateURLs(c, retrievedURLs, retrievedURLsWD, iteration)
        
          
        if c.debug:
            print("   Maintained URLs...")
            for url in c.URLs:
                print("      " + str(url))
        
        if c.debug:
            print("   Newly obtained URLs (duplicates may occur) ...")
            for url in retrievedURLs:
                    print("      " + str(url))
        if c.debug:
            print("   Newly obtained URLs (without duplicates) ...")
            for url in retrievedURLsWD:
                    print("      " + str(url))        
        for url in retrievedURLsWD:
            c.URLs.add(url)

    
    if c.storeURLs:
        storeURLs(c)
    if c.storeOutgoingURLs:
        storeOutgoingURLs(c)
    if c.storeIncomingURLs:
        storeIncomingURLs(c)            
    

# Inject seed URL into a queue (DONE)
def inject(c):
    for l in c.seedURLs:
        if c.debug: 
            print("Injecting " + str(l))
        c.URLs.add(l)

# Produce next URL to be fetched (DONE)
def generate(c, iteration):
    url = c.generatePolicy.getURL(c, iteration)
    if url == None:
        if c.debug:
            print("   Fetch: error")
        c.toFetch = None
        return None
    
    print("   Next page to be fetched = " + str(url)) 
    c.toFetch = url
    

# Generate (download html) page (DONE)
def fetch(c):
    URL = c.toFetch
    if c.debug: 
        print("   Downloading " + str(URL))
    try:
        opener = req.build_opener()
        opener.addheadders = [('User-Agent', c.crawlerName)]
        webPage = opener.open(URL)
        return webPage
    except:
        return None 
        
 

def removeWrongURL(c):
    c.URLs.remove(c.toFetch)
    
 
# Parse this page and retrieve text (whole page) and URLs (DONE)
def parse(c, page, iteration):
    htmlData = page.read()
    p = Parser()
    p.feed(str(htmlData))
    retrievedURLs = set(p.output_list)

    if c.debug:
        print("   Extracted " + str(len(retrievedURLs)) + " links")


    return htmlData, retrievedURLs


def getNormalisedURLs(retrievedURLs):
    retrievedURLs = set([url.lower() for url in retrievedURLs])
    return retrievedURLs
    
 

def removeDuplicates(c, retrievedURLs):
    retrievedURLs = [url for url in retrievedURLs if url not in c.URLs] 
    return retrievedURLs

 

def getFilteredURLs(c, retrievedURLs):
    toLeft = set([url for url in retrievedURLs if url.lower().startswith(c.rootPage)])
    remainingURLs = set([url for url in toLeft if not url.lower() == c.toFetch.lower()])
    if c.debug:
        print("   Filtered out " + str(len(retrievedURLs) - len(remainingURLs)) + " urls")  
    return remainingURLs
    
 
 
def storePage(c, htmlData):
    relBeginIndex = len(c.rootPage)
    totalPath = "./" + c.example + "/pages/" + c.toFetch[relBeginIndex + 1:]
    
    if c.debug:
        print("   Saving HTML page " + totalPath + "...")
    
    totalDir = os.path.dirname(totalPath)
    
    if not os.path.exists(totalDir):
        os.makedirs(totalDir)
        
    with open(totalPath, "wb+") as f:
        f.write(htmlData)
        f.close()
        
 

def storeURLs(c):
    relBeginIndex = len(c.rootPage)
    totalPath = "./" + c.example + "/urls/urls.txt"
    
    if c.debug:
        print("Saving URLs " + totalPath + "...")
    
    totalDir = os.path.dirname(totalPath)
    
    if not os.path.exists(totalDir):
        os.makedirs(totalDir)
        
    data = [url for url in c.URLs]
    data.sort()
        
    with open(totalPath, "w+") as f:
        for line in data:
            f.write(line + "\n")
        f.close()
        
 
def updateOutgoingURLs(c, retrievedURLsWD):
    if c.toFetch not in c.outgoingURLs:
        c.outgoingURLs[c.toFetch] = set([])
    for url in retrievedURLsWD:
        c.outgoingURLs[c.toFetch].add(url)
        
 
def updateIncomingURLs(c, retrievedURLsWD):
    for url in retrievedURLsWD:
        if url not in c.incomingURLs:
            c.incomingURLs[url] = set([])
        c.incomingURLs[url].add(c.toFetch)
    
 
def storeOutgoingURLs(c):
    relBeginIndex = len(c.rootPage)
    totalPath = "./" + c.example + "/outgoing_urls/outgoing_urls.txt"
    
    if c.debug:
        print("Saving URLs " + totalPath + "...")
    
    totalDir = os.path.dirname(totalPath)
    
    if not os.path.exists(totalDir):
        os.makedirs(totalDir)
        
    data = [url for url in c.outgoingURLs]
    data.sort()
        
    with open(totalPath, "w+") as f:
        for line in data:
            s = list(c.outgoingURLs[line])
            s.sort()
            for l in s:
                f.write(line + " " + l + "\n")
        f.close()
        

def storeIncomingURLs(c):
    relBeginIndex = len(c.rootPage)
    totalPath = "./" + c.example + "/incoming_urls/incoming_urls.txt"
    
    if c.debug:
        print("Saving URLs " + totalPath + "...")
    
    totalDir = os.path.dirname(totalPath)
    
    if not os.path.exists(totalDir):
        os.makedirs(totalDir)
        
    data = [url for url in c.incomingURLs]
    data.sort()
        
    with open(totalPath, "w+") as f:
        for line in data:
            s = list(c.incomingURLs[line])
            s.sort()
            for l in s:
                f.write(line + " " + l + "\n")
        f.close()
        

if __name__ == "__main__":
    main()
