import heapq
import copy

tab_final = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 0]]

class inputAStar:
  def __init__(self, matriz, pai, sucessores, g, h):
    self.tabuleiro = copy.deepcopy(matriz)
    self.g = g
    self.h = h
    self.pai = pai
    self.sucessores = sucessores

  def f(self):
    return self.g + self.h

  def add_sucessor(self, sucessor):
    self.sucessores.append(sucessor)


def geraSucessores(node):
  matriz = copy.deepcopy(node.tabuleiro)
  i = j = 0
  while (True):
    if (j == 4):
      j = 0
      i += 1
    if(matriz[i][j] == 0):
      break
    else:
      j += 1
  if(i > 0):
    cima = copy.deepcopy(matriz)
    temp = cima[i][j]
    cima[i][j] = cima[i-1][j]
    cima[i-1][j] = temp
    node.add_sucessor(inputAStar(cima, [], [], node.g + 1, 0))
  if(j > 0):
    esquerda = copy.deepcopy(node.matriz)
    temp = esquerda[i][j]
    esquerda[i][j] = esquerda[i][j-1]
    esquerda[i][j-1] = temp 
    node.add_sucessor(inputAStar(esquerda, [], [], node.g + 1, 0))
  if(i < 3):
    baixo = copy.deepcopy(node.matriz)
    temp = baixo[i][j]
    baixo[i][j] = baixo[i+1][j]
    baixo[i+1][j] = temp
    node.add_sucessor(inputAStar(baixo, [], [], node.g + 1, 0))
  if(j < 3):
    direita = copy.deepcopy(node.matriz)
    temp = direita[i][j]
    direita[i][j] = direita[i][j+1]
    direita[i][j+1] = temp
    node.add_sucessor(inputAStar(direita, [], [], node.g + 1, 0))


def montaTabuleiro(entrada):
  read = input().split(' ')
  read = [num for num in read if num]
  k = 0

  for i in range(0, 4):
    for j in range(0, 4):
      entrada[i][j] = int(read[k])
      k += 1


def h1(tabuleiro):
  foraDoLugar = 0
  for (indice, i) in enumerate(tabuleiro):
    for j in range(len(i)):
      if (i[j] != tab_final[indice][j]):
        foraDoLugar += 1
  return foraDoLugar

def h2(tabuleiro):
  foraDoLugar = 0
  for i in enumerate(tabuleiro):
    for j in range(len(i)):
      if(i[j+1] != i[j] + 1 ):
        foraDoLugar += 1
  return foraDoLugar

def h3(tabuleiro):
  soma = 0
  for i in range(4):
    for j in range(4):
      if(tabuleiro[i][j] == 0):
        soma += 3-i + 3-j
      else:
        i0 = (tabuleiro[i][j] - 1) // 4
        j0 = (tabuleiro[i][j] - 1) % 4
        soma += abs(i - i0) + abs(j - j0)
  return soma

def h5(tabuleiro):
  return max(h1(tabuleiro), h2(tabuleiro), h3(tabuleiro))


def astar(tabuleiro):
  T = str(tab_final)
  A = {}
  F = {}
  heap = []
  A[str(tabuleiro)] = inputAStar(tabuleiro, [], [], 0, h3(tabuleiro))
  heapq.heappush(heap, (A[str(tabuleiro)].f(), str(tabuleiro))) #adiciona pro heap heap o F do tabuleiro, e o tabuleiro inicial
  v = A[str(tabuleiro)]
  while A and (str(v.tabuleiro) != T):
    while True:
      pos = heapq.heappop(heap)
      if (pos[1] in A):
        break
    v = A.get(pos[1])
    A.pop(str(v.tabuleiro))
    F[str(v.tabuleiro)] = v
    if not v.sucessores:
      geraSucessores(v)
    m = v.sucessores
    for i in range(0, len(v.sucessores)):
      m_linha = str(m[i].matriz)
      if(m_linha in A and m[i].g < A[m_linha].g):
        A.pop(m_linha)
      if(m_linha not in A and m_linha not in F):
        A[str(m[i].tabuleiro)] = m[i]
        A[str(m[i].tabuleiro)].pai = v
        A[str(m[i].tabuleiro)].h = h3(m[i].matriz)
        heapq.heappush(heap, (A[str(m[i].tabuleiro)].f(), str(m[i].tabuleiro)))
  return v.g


def main():
  inicial = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
  montaTabuleiro(inicial)
  print(astar(inicial))


if __name__ == '__main__':
  main()
