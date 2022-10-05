import pygame
import random as rd
import math

pygame.init()
r = 15
HEIGHT = 800
WIDTH = 800
SCWIDTH = 1000
TOTW = SCWIDTH
TOTH = HEIGHT
screen = pygame.display.set_mode((SCWIDTH, HEIGHT))
end = False
timer = pygame.time.Clock()
id = 0
kulki = []
view = []
buttons = []
timestep = 1 / (15 * 100)
srednia = 0
droga = []
time = 0
globaltime = 0
d = 1 / 10 * r
M = 1500 * 90
n = 0


def setHW(x):
    global HEIGHT
    global WIDTH
    global kulki
    global id
    global view
    global r
    id = 0
    if x > 0 and x >= 2 * r:
        HEIGHT = int(x)
        WIDTH = int(x)
        kulki = [kulka(r, HEIGHT - r, 0, 0, r, (255, 0, 0), id)]
        id = 1
        view[0].curh = "0"
        view[0].curw = "0"


def setR(x):
    global HEIGHT
    global WIDTH
    global kulki
    global id
    global view
    global r
    id = 0
    if 0 < x < WIDTH:
        r = int(x)
        kulki = [kulka(r, HEIGHT - r, 0, 0, r, (255, 0, 0), id)]
        id = 1
        view[0].curr = "0"


class viewport:
    def __init__(self, x, y, w, h):
        self.w = w
        self.h = h
        self.x = x
        self.y = y
        self.curw = "0"
        self.curh = "0"
        self.curr = "0"
        self.font = pygame.font.Font('freesansbold.ttf', 17)
        self.but = ""

    def set(self):
        if self.but == "W":
            setHW(int(self.curw))
        elif self.but == "H":
            setHW(int(self.curh))
        elif self.but == "R":
            setR(int(self.curr))

    def update(self, x):

        if self.but == "W":
            self.curw = str(int(self.curw) * 10 + x)
        elif self.but == "H":
            self.curh = str(int(self.curh) * 10 + x)
        elif self.but == "R":
            self.curr = str(int(self.curr) * 10 + x)

    def text_objects(self, text, font, col=(255, 255, 255)):
        textsurface = font.render(text, True, col)
        return textsurface, textsurface.get_rect()

    def show(self, x, y, id, vx, vy):
        global globaltime
        global HEIGHT
        global n
        text1 = "v = " + str(((vx ** 2) + (vy ** 2)) ** 0.5)
        text2 = "x = " + str(x)
        text3 = "y = " + str(HEIGHT - y)
        text4 = "λ  = " + str(id)
        text5 = "n  = " + str(n)
        surf1, rect1 = self.text_objects(text1, self.font)
        surf2, rect2 = self.text_objects(text2, self.font)
        surf3, rect3 = self.text_objects(text3, self.font)
        surf4, rect4 = self.text_objects(text4, self.font)
        surf5, rect5 = self.text_objects(text5, self.font)
        rect1.center = ((SCWIDTH - 800) / 2 + 800, 25)
        rect2.center = ((SCWIDTH - 800) / 2 + 800, 75)
        rect3.center = ((SCWIDTH - 800) / 2 + 800, 125)
        rect4.center = ((SCWIDTH - 800) / 2 + 800, 175)
        rect5.center = ((SCWIDTH - 800) / 2 + 800, 225)
        screen.blit(surf1, rect1)
        screen.blit(surf2, rect2)
        screen.blit(surf3, rect3)
        screen.blit(surf4, rect4)
        screen.blit(surf5, rect5)

    def show2(self):
        pygame.draw.rect(screen, (150, 150, 150), (self.x, self.y, self.w, self.h))
        if self.curw == "0":
            text1 = "WIDTH = " + str(WIDTH)
        else:
            text1 = "WIDTH = " + str(self.curw)
        if self.curh == "0":
            text2 = "HEIGHT = " + str(HEIGHT)
        else:
            text2 = "HEIGHT = " + str(self.curh)
        if self.curr == "0":
            text3 = "R = " + str(r)
        else:
            text3 = "R = " + str(self.curr)
        surf1, rect1 = self.text_objects(text1, self.font, (0, 0, 0))
        surf2, rect2 = self.text_objects(text2, self.font, (0, 0, 0))
        surf3, rect3 = self.text_objects(text3, self.font, (0, 0, 0))
        rect1.center = ((750 - 450) / 2 + 450, 250)
        rect2.center = ((750 - 450) / 2 + 450, 300)
        rect3.center = ((750 - 450) / 2 + 450, 350)
        screen.blit(surf1, rect1)
        screen.blit(surf2, rect2)
        screen.blit(surf3, rect3)


def change():
    global view
    global buttons
    view.append(viewport(450, 200, 300, 300))
    for z in buttons:
        if z.fun != z.cha:
            z.act = False
    buttons.append(button(450, 200, 300, 50, (0, 0, 0), 5))
    buttons.append(button(450, 250, 300, 50, (0, 0, 0), 5))
    buttons.append(button(450, 310, 300, 50, (0, 0, 0), 6))


class kulka:
    def __init__(self, x, y, vx, vy, rad, color, id):
        self.posx = x
        self.posy = y
        self.velx = vx
        self.vely = vy
        self.r = rad
        self.col = color
        self.id = id

    def move(self):
        if self.posx + self.velx + self.r < WIDTH and self.posx + self.velx - self.r > 0:
            self.posx += self.velx
        elif self.posx + self.velx + self.r >= WIDTH:
            self.posx = WIDTH - (self.posx + self.velx + self.r - WIDTH) - self.r
            self.velx = -self.velx
        else:
            self.posx = -((self.posx - self.r) + self.velx) + self.r
            self.velx = - self.velx
        if self.posy + self.vely + self.r < HEIGHT and self.posy + self.vely - self.r > 0:
            self.posy += self.vely
        elif self.posy + self.vely + self.r >= HEIGHT:
            self.posy = HEIGHT - (self.posy + self.vely + self.r - HEIGHT) - self.r
            self.vely = -self.vely
        else:
            self.posy = -((self.posy - self.r) + self.vely) + self.r
            self.vely = - self.vely

    def show(self):
        pygame.draw.circle(screen, self.col, (int(self.posx), int(self.posy)), self.r)

    def clicked(self):
        click = pygame.mouse.get_pressed()
        pos = pygame.mouse.get_pos()
        if click[0] == 1 and (pos[0] - self.posx) ** 2 + (pos[1] - self.posy) ** 2 <= self.r ** 2:
            return True
        else:
            return False


kulki = []
tocal = []


def collision():
    global droga
    global time
    global srednia
    for ball1 in kulki:
        for ball2 in kulki:
            if ball1.id != ball2.id:
                if (ball1.posx - ball2.posx) ** 2 + (ball1.posy - ball2.posy) ** 2 <= (ball1.r + ball2.r) ** 2:
                    dist = ((ball1.posx - ball2.posx) ** 2 + (ball1.posy - ball2.posy) ** 2) ** 0.5
                    shift = (dist - ball1.r - ball2.r) / 2

                    ball1.posx -= shift * (ball1.posx - ball2.posx) / dist
                    ball1.posy -= shift * (ball1.posy - ball2.posy) / dist

                    ball2.posx += shift * (ball1.posx - ball2.posx) / dist
                    ball2.posy += shift * (ball1.posy - ball2.posy) / dist

                    tocal.append((ball1, ball2))
                    if ball1.id == 0 or ball2.id == 0:
                        newtime = pygame.time.get_ticks() / 1000
                        since = newtime - time
                        droga.append(since * (kulki[0].velx ** 2 + kulki[0].vely ** 2) ** 0.5)
                        srednia = sum(droga) / len(droga)
                        time = newtime


def vcal():
    global tocal
    for par in tocal:
        ball1 = par[0]
        ball2 = par[1]
        dist = ((ball1.posx - ball2.posx) ** 2 + (ball1.posy - ball2.posy) ** 2) ** 0.5
        nx = (ball2.posx - ball1.posx) / dist
        ny = (ball2.posy - ball1.posy) / dist
        tx = -ny
        ty = nx
        dptan1 = ball1.velx * tx + ball1.vely * ty
        dptan2 = ball2.velx * tx + ball2.vely * ty

        dpnor1 = ball1.velx * nx + ball1.vely * ny
        dpnor2 = ball2.velx * nx + ball2.vely * ny

        m1 = dpnor2
        m2 = dpnor1

        ball1.velx = tx * dptan1 + nx * m1
        ball1.vely = ty * dptan1 + ny * m1
        ball2.velx = tx * dptan2 + nx * m2
        ball2.vely = ty * dptan2 + ny * m2
    tocal = []


class button:
    def add(self, x, y):
        global id
        vx = rd.randint(-15, 15)
        vy = rd.randint(-15, 15)
        while True:
            px = rd.randint(r, WIDTH - r)
            py = rd.randint(r, HEIGHT - r)
            czy = True
            for z in kulki:
                if (px - z.posx) ** 2 + (py - z.posy) ** 2 <= (z.r * 2) ** 2:
                    czy = False
                    break
            if czy:
                break
        kulki.append(kulka(px, py, vx, vy, r, (100, 100, 250), id))
        id += 1
        y[0] += ((vx ** 2) + (vy ** 2)) ** 0.5

    def start(self, x, y):
        x[0] = False

    def pause(self, x, y):
        x[0] = not x[0]

    def res(self, x, y):
        global n
        global globaltime
        x[0] = False
        n = len(droga) / ((pygame.time.get_ticks() / 1000) - globaltime)
        y()

    def cha(self, x, y):
        global buttons
        global view
        if view:
            view = []
            buttons = [button(800 + 20, 300, SCWIDTH - 40 - 800, 50, (200, 0, 0), 0),
                       button(800 + 20, 450, SCWIDTH - 40 - 800, 50, (0, 200, 0), 1),
                       button(800 + 20, 600, SCWIDTH - 40 - 800, 50, (100, 200, 0), 4)]
        else:
            change()

    def sHW(self, x, y):
        view[0].but = "W"
        print(view[0].but)

    def sR(self, x, y):
        view[0].but = "R"

    def __init__(self, x, y, w, h, c, fun):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.col = c
        self.act = True
        if fun == 0:
            self.fun = self.add
        elif fun == 1:
            self.fun = self.start
        elif fun == 2:
            self.fun = self.pause
        elif fun == 3:
            self.fun = self.res
        elif fun == 4:
            self.fun = self.cha
        elif fun == 5:
            self.fun = self.sHW
        elif fun == 6:
            self.fun = self.sR

    def onclick(self, x=5, y=6):
        click = pygame.mouse.get_pressed()
        pos = pygame.mouse.get_pos()
        if self.act and click[0] == 1 and self.x <= pos[0] <= self.x + self.w and self.y <= pos[1] <= self.y + self.h:
            ret = self.fun(x, y)
            pygame.time.wait(50)

    def show(self):
        pygame.draw.rect(screen, self.col, (self.x, self.y, self.w, self.h))


buttons = []
hud = viewport(WIDTH, 0, SCWIDTH - WIDTH, 300)


def pocz():
    pygame.time.wait(100)
    global id
    global kulki
    global buttons
    global view
    global n
    global globaltime
    global droga
    global srednia
    v = [0]
    id = 0
    kulki = []
    buttons = [button(WIDTH + 20, 300, SCWIDTH - 40 - WIDTH, 50, (200, 0, 0), 0),
               button(WIDTH + 20, 450, SCWIDTH - 40 - WIDTH, 50, (0, 200, 0), 1),
               button(WIDTH + 20, 600, SCWIDTH - 40 - WIDTH, 50, (100, 200, 0), 4)]
    newkul = []
    run = [True]
    cre = False
    kulki.append(kulka(r, HEIGHT - r, 0, 0, r, (255, 0, 0), id))
    id += 1
    track = kulki[0]
    while run[0]:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif view and event.type == pygame.KEYDOWN:
                if event.key == pygame.K_0:
                    view[0].update(0)
                elif event.key == pygame.K_1:
                    view[0].update(1)
                elif event.key == pygame.K_2:
                    view[0].update(2)
                elif event.key == pygame.K_3:
                    view[0].update(3)
                elif event.key == pygame.K_4:
                    view[0].update(4)
                elif event.key == pygame.K_5:
                    view[0].update(5)
                elif event.key == pygame.K_6:
                    view[0].update(6)
                elif event.key == pygame.K_7:
                    view[0].update(7)
                elif event.key == pygame.K_8:
                    view[0].update(8)
                elif event.key == pygame.K_9:
                    view[0].update(9)
                elif event.key == pygame.K_RETURN:
                    view[0].set()

        mysz = pygame.mouse.get_pos()
        click = pygame.mouse.get_pressed()

        if click[0] == 1 and cre and view == []:
            kulki.append(kulka(newkul[0], newkul[1], mysz[0] - newkul[0], mysz[1] - newkul[1], r, (100, 100, 250), id))
            id += 1
            v[0] += ((mysz[0] - newkul[0]) ** 2 + (mysz[1] - newkul[1]) ** 2) ** 0.5
            newkul = []
            cre = False
        elif mysz[0] <= WIDTH and view == [] and mysz[1] <= HEIGHT:
            czy = True
            for x in kulki:
                if (mysz[0] - x.posx) ** 2 + (mysz[1] - x.posy) ** 2 <= (x.r * 2) ** 2:
                    czy = False
            if czy:
                if click[0] == 1 and r <= mysz[0] <= WIDTH - r and not cre:
                    newkul.append(mysz[0])
                elif click[0] == 1 and mysz[0] < r and not cre:
                    newkul.append(r)
                elif click[0] == 1 and mysz[0] > WIDTH - r and not cre:
                    newkul.append(WIDTH - r)
                if click[0] == 1 and r <= mysz[1] <= HEIGHT - r and not cre:
                    newkul.append(mysz[1])
                    cre = True
                elif click[0] == 1 and mysz[1] < r and not cre:
                    newkul.append(r)
                    cre = True
                elif click[0] == 1 and mysz[1] > HEIGHT - r and not cre:
                    newkul.append(HEIGHT - r)
                    cre = True
        screen.fill((0, 0, 0))
        pygame.draw.rect(screen, (0, 0, 80), (0, 0, TOTW, TOTH))
        pygame.draw.rect(screen, (0, 0, 0), (0, 0, WIDTH, HEIGHT))
        for k in kulki:
            k.show()
            if k.clicked():
                track = k
        if cre:
            pygame.draw.circle(screen, (100, 100, 250), (newkul[0], newkul[1]), r)
            pygame.draw.line(screen, (0, 200, 0), (newkul[0], newkul[1]), (mysz[0], mysz[1]))
        pygame.draw.rect(screen, (0, 0, 80), (WIDTH, 0, SCWIDTH - WIDTH, HEIGHT))

        for b in buttons:
            b.show()
            b.onclick(run, v)
        for z in view:
            z.show2()
        hud.show(track.posx, track.posy, srednia, track.velx, track.vely)
        pygame.display.update()
        pygame.time.wait(50)
    buttons = [button(800 + 20, 300, SCWIDTH - 40 - 800, 50, (0, 0, 200), 2),
               button(800 + 20, 450, SCWIDTH - 40 - 800, 50, (100, 100, 100), 3)]

    kulki[0].velx = rd.randint(0, 15)
    kulki[0].vely = rd.randint(0, 15)
    globaltime = pygame.time.get_ticks()/1000
    time = 0
    srednia = 0
    n = 0
    droga = []


pocz()
pause = [False]
track = kulki[0]
while not end:
    screen.fill((0, 0, 0))
    pygame.draw.rect(screen, (0, 0, 80), (0, 0, TOTW, TOTH))
    pygame.draw.rect(screen, (0, 0, 0), (0, 0, WIDTH, HEIGHT))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            end = True
    for kul in kulki:
        if not pause[0]:
            kul.move()
    collision()
    vcal()
    for kul in kulki:
        kul.show()
        if kul.clicked():
            track = kul
    pygame.draw.rect(screen, (0, 0, 80), (WIDTH, 0, SCWIDTH - WIDTH, HEIGHT))
    for b in buttons:
        b.show()
        b.onclick(pause, pocz)
    hud.show(track.posx, track.posy, srednia, track.velx, track.vely)
    pygame.display.update()
    if pygame.time.get_ticks() / 1000 - globaltime>= timestep * M:
        n = len(droga) / ((pygame.time.get_ticks() / 1000) - globaltime)
        pocz()
    print(pygame.time.get_ticks() / 1000 - globaltime,timestep * M)
    timer.tick(60)
pygame.quit()
quit()
