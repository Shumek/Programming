#Поиск новостей на сайте фонтанка.ру(с возможностью фильтрации по дате)
#импорт библиотек для подключения к URL
import urllib
import urllib.request
searchword = input("Ввндите слово или словосочетание: ")
data = input("С какого числа искать(вводить по типу гггг/мм/дд): ")
data2 = input("По какое число искать(вводить по типу гггг/мм/дд): ")
#Переводим из char в int
g = int(data[:4])
m = int(data[5:7])
d = int(data[8:10])
g2 = int(data2[:4])
m2 = int(data2[5:7])
d2 = int(data2[8:10])
num = searchword.find(' ')
word = searchword[:num]
word2 = searchword[num+1:]
lim404 = 0
searchnews = 0
i=0
urlarr = ['Содержит словосочетание']
urlarr2 =['Содержит одно слово']
urlob = []
flag = 0
while g<=g2 and m<=m2 and d<=d2:
    if d == 32:
        m+=1
        d=0
    if m == 13:
       g+=1
       m=0
    if d < 10:
        day = "0"+str(d)
    if m < 10:
        month = "0"+str(m)
    #Номер новости
    k=1
    while k<=100:
        
        if k < 10:
            news = "00"+str(k)
        elif k >= 10 and k < 100:
            news = "0"+str(k)
        else:
            news = str(k)
        #URL
        url = "http://www.fontanka.ru/"+str(g)+"/"+month+"/"+day+"/"+news+"/"
        #print(url)
        #попытка открытия страницы
        try:
            result = urllib.request.urlopen(url)
        except Exception as E:
            #счётчик подряд отсутствующих страниц увеличить на 1
            lim404 += 1
            if lim404 > 3:
                break
        else:
                #счётчик подряд отсутствующих страниц обнулить
            lim404 = 0
            try:
                content = result.read().decode('cp1251')
            except Exception as E:
                pass
            else:
                flag=0
                if content.find("<h1>") >= 0 and content.find("<g:plusone") >= 0:
                    #позиция первой встречи <h1>
                    begin = content.find("<h1>")
                    #позиция последней встречи <g:plusone>
                    end = content.find("<g:plusone")
                    #если в срезе между первым <p> и последним </p> есть искомое слово,
                    #то увеличить счётчик искомых слов
                    if content[begin:end].find(searchword) >= 0:
                        #увеличить счётчик страниц с запросом
                        searchnews += 1
                      #  print(url)
                        urlarr.append(url)
                        #если выражение нашлось целиком, то flag=1
                        flag=1
                    if content[begin:end].find(word)>=0 and flag==0:
                        #print(url)
                        urlarr2.append(url)
                    elif content[begin:end].find(word2)>=0 and flag==0:
                       # print(url)
                        urlarr2.append(url)
            k+=1            
    d+=1
urlob = urlarr + urlarr2
for p in range(len(urlob)):
    print(urlob[p])


    
