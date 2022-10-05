from CTScanner import *
from Image import *
from Algorithms import *

SheppLogan_path = "images/Shepp_logan.jpg"
Kolo_path = "images/Kolo.jpg"
Kropka_path = "images/Kropka.jpg"
Kwadraty2_path = "images/Kwadraty2.jpg"
Paski2_path = "images/Paski2.jpg"


def main():
    testImage = Image(SheppLogan_path)


    testCTScanner = CTScanner(testImage.centerWithPadding, testImage.sizeWithPadding//2, 180,  160, 181, testImage.getImageWithPadding(), 180)

    # plt.imshow(testImage.getImage(), cmap="gray")

    testCTScanner.calcSinogramData()
    testCTScanner.calcResultData()

    testCTScanner.plotSinogram()
    testCTScanner.plotResult()

if __name__ == "__main__":
    main()