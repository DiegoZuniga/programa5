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

#lee las lineas del archivo de jugadas, hasta encontrar la generada por randint
def obtieneJugada(limite,arch):
	jugada=""
	num_jugada=randint(1,limite)
	cont=1
	f1=open(arch,"r")
	for x in f1:
		if cont==num_jugada:
			jugada=x
			break
		cont=cont+1
	f1.close()
	lista = list(jugada[:-1].split(" ")) 
	print(lista)
	return lista

#el limite es para generar un random, que determine qué jugada se va a reproducir
def obtieneLimite(arch,res):
	f1=open(arch,"r")
	limite=len(f1.readlines())
	if limite==0:
		f1.close()
		arch=res
		f1=open(arch,"r")
		limite=len(f1.readlines())
		print("sin jugadas ganadoras, cambio de archivo de lectura a "+arch)
	f1.close()
	#print(limite)
	return limite,arch 

def obtieneListaMenor(l1,l2):
	if len(l1)>=len(l2):
		return l2
	return l1
#revisa si las fichas pueden colocarse en una misma posicion
#puede que sean en el mismo turno o no, depende quien tira primero
#retorna true si coinciden y cambia la lista del jugador 1, siempre el jugador 1
#podría cambiar ambas
def coinciden(cant_min,lista1,limite1,lista2,arch):
	listaCambiada=lista1
	bandera=False
	for i in range(0,cant_min):
		if i<cant_min-1 and i>0:
			if lista1[i]==lista2[i] or lista1[i]==lista2[i+1]  or lista1[i]==lista2[i-1]:
				print("Se coincide en algun punto, cambio de lista de jugadas")
				limite1,arch=obtieneLimite(arch,respaldo)
				listaCambiada=obtieneJugada(limite1,arch)
				bandera=True
	return listaCambiada,bandera


limite1,archivo=obtieneLimite(archivo,respaldo)
lista_jugada = obtieneJugada(limite1,archivo)

if cantidad_jugadores=="2":
	limite2,archivo2=obtieneLimite(archivo2,respaldo2)
	lista_jugada2=obtieneJugada(limite2,archivo2)
	#esto nomas es para iterar sobre la lista con menor cantidad de movimientos
	#y no entrar en posiciones que no existen
	#el juego termina cuando se ejecuta la cantidad mínima de tiradas (alqguien gana o simplemente terminan)
	lista_menor=obtieneListaMenor(lista_jugada,lista_jugada2)
	#esta variable es una herramienta que nos ayudara mas tarde
	minJugadas=len(lista_menor)

	#verifica que no coincida una misma posición en una misma tirada
	lista_jugada,band=coinciden(minJugadas, lista_jugada, limite1, lista_jugada2, archivo)
	
	while band:
		lista_menor=obtieneListaMenor(lista_jugada,lista_jugada2)
		minJugadas=len(lista_menor)
		lista_jugada,band=coinciden(minJugadas, lista_jugada, limite1, lista_jugada2, archivo)


	print(tira_primero+" comienza el juego")

pygame.init()
#activar el while para que no se cierre la pantalla de ejecucion
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
						
					pantalla.blit(ficha2,coords.get(int(lista_jugada2[aux])))
					pantalla.blit(ficha1, coords.get(int(lista_jugada[aux-1])))
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
						
					pantalla.blit(ficha2,coords.get(int(lista_jugada[aux])))
					pantalla.blit(ficha1, coords.get(int(lista_jugada2[aux-1])))
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
