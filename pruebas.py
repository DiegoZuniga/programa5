import pygame
from pygame.locals import *
from random import randint
import sys

cantidad_jugadores=sys.argv[1]
jugador=sys.argv[2]
tira_primero=sys.argv[3]

pantalla = pygame.display.set_mode((400, 400))
pygame.display.set_caption('Tablero de juego')

reloj = pygame.time.Clock()

"""cargar las imagenes que se utilizan"""
fondo = pygame.image.load('tablero.png')
ficha1 = pygame.image.load("fichaP1.png")
ficha2 = pygame.image.load("fichaP2.png")
#Asigan las coordenadas donde pueden posicionarse las fichas
coords={}
cont=1
for i in range (0,4):
	for j in range (0,4):
		coords[cont]=(100*(j) +12 , 100*(i)+12 )
		cont=cont+1
#abre archivos donde estan las jugadas
if jugador=="1":
	archivo="jugadas_ganadoras_p1.txt"
	archivo2="jugadas_ganadoras_p2.txt"
	respaldo="all_plays_p1.txt"
	respaldo2="all_plays_p2.txt"
else:
	archivo="jugadas_ganadoras_p2.txt"
	archivo2="jugadas_ganadoras_p1.txt"
	respaldo="all_plays_p2.txt"
	respaldo2="all_plays_p1.txt"



f1=open(archivo,"r")
limite=len(f1.readlines())
if limite==0:
	print("no tienes jugadas ganadoras, cambio de archivo de lectura")
	f1.close()
	archivo=respaldo
	f1=open(archivo,"r")
	limite=len(f1.readlines())

f1.close()
jugada=""
num_jugada=randint(1,limite)
cont=1
f1=open(archivo,"r")
for x in f1:
	if cont==num_jugada:
		jugada=x
		break
	cont=cont+1
f1.close()
lista_jugada = list(jugada[:-1].split(" ")) 
print(lista_jugada)

if cantidad_jugadores=="2":
	f2=open(archivo2,"r")
	limite=len(f2.readlines())
	if limite==0:
		print("tu oponente no tiene jugadas ganadoras, cambio de archivo de lectura")
		f2.close()
		archivo2=respaldo2
		f2=open(archivo2,"r")
		limite=len(f2.readlines())


	f2.close()
	jugada=""
	num_jugada2=randint(1,limite)
			#jugadas=f1.readlines()
	cont=1
	f2=open(archivo2,"r")
	for x in f2:
		if cont==num_jugada2:
			jugada=x
			break
		cont=cont+1
			#print(jugada)
	f2.close()
		#print(coords)
	lista_jugada2 = list(jugada[:-1].split(" ")) 
	print(lista_jugada2)

	if len(lista_jugada)>=len(lista_jugada2):
		lista_menor=lista_jugada2
		#lista_mayor=lista_jugada
		#print("has perdido")
	else:
		lista_menor=lista_jugada
		#lista_mayor=lista_jugada2
		#print("Has ganado")
	print(tira_primero+" comienza el juego")

pygame.init()
#while 1:
for event in pygame.event.get():
	if event.type == pygame.QUIT:
		exit()
if cantidad_jugadores=="2":
	aux=0
	pantalla.blit(fondo,(0,0))
	pantalla.blit(ficha1,coords.get(1))
	pantalla.blit(ficha2,coords.get(4))
	pygame.display.flip()
	if tira_primero=="1":
		if jugador=="1":
			for c in lista_menor:
				if aux>0:
					pantalla.blit(fondo,(0,0))
							
					pantalla.blit(ficha1,coords.get(int(lista_jugada[aux])))
					pantalla.blit(ficha2, coords.get(int(lista_jugada2[aux-1])))
					pygame.display.flip()
					pygame.time.wait(1000)
						
					pantalla.blit(fondo,(0,0))
					pantalla.blit(ficha2,coords.get(int(lista_jugada2[aux])))
					pantalla.blit(ficha1,coords.get(int(lista_jugada[aux])))
					pygame.display.flip()

				pygame.time.wait(1000)
				aux=aux+1
		else:
			for c in lista_menor:
				if aux>0:
					pantalla.blit(fondo,(0,0))
							
					pantalla.blit(ficha1,coords.get(int(lista_jugada2[aux])))
					pantalla.blit(ficha2, coords.get(int(lista_jugada[aux-1])))
					pygame.display.flip()
					pygame.time.wait(1000)
						
					pantalla.blit(fondo,(0,0))
					pantalla.blit(ficha2,coords.get(int(lista_jugada[aux])))
					pantalla.blit(ficha1,coords.get(int(lista_jugada2[aux])))
					pygame.display.flip()

				pygame.time.wait(1000)
				aux=aux+1
	elif tira_primero=="2":
		if jugador=="1":

			for c in lista_menor:
				if aux>0:
					pantalla.blit(fondo,(0,0))
						
					pantalla.blit(ficha2,coords.get(int(lista_jugada2[aux-1])))
					pantalla.blit(ficha1, coords.get(int(lista_jugada[aux])))
					pygame.display.flip()
					pygame.time.wait(1000)
					
					pantalla.blit(fondo,(0,0))
					pantalla.blit(ficha2,coords.get(int(lista_jugada2[aux])))
					pantalla.blit(ficha1,coords.get(int(lista_jugada[aux])))
					pygame.display.flip()

				pygame.time.wait(1000)
				aux=aux+1
		else:
			for c in lista_menor:
				if aux>0:
					pantalla.blit(fondo,(0,0))
						
					pantalla.blit(ficha2,coords.get(int(lista_jugada1[aux-1])))
					pantalla.blit(ficha1, coords.get(int(lista_jugada2[aux])))
					pygame.display.flip()
					pygame.time.wait(1000)
					
					pantalla.blit(fondo,(0,0))
					pantalla.blit(ficha2,coords.get(int(lista_jugada[aux])))
					pantalla.blit(ficha1,coords.get(int(lista_jugada2[aux])))
					pygame.display.flip()

				pygame.time.wait(1000)
				aux=aux+1
else:
	if jugador=="1":
		ficha=ficha1
	else:	
		ficha=ficha2
	for c in lista_jugada:
		pantalla.blit(fondo,(0,0))
		pantalla.blit(ficha,coords.get(int(c)))
		pygame.display.flip()
		pygame.time.wait(1000)
