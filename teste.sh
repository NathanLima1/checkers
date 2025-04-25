#!/usr/bin/env bash
#
# test_tp1.sh
# Gera entradas aleatórias no formato correto, executa ./tp1 com e sem -f, compara resultados.

MAX_SIZE=20

while true; do
  # 1) Gera m e n aleatórios entre 1 e MAX_SIZE
  m=$(( RANDOM % MAX_SIZE + 1 ))
  n=$(( RANDOM % MAX_SIZE + 1 ))
  total=$(( (m * n + 1) / 2 ))  # número de casas válidas (pretas)

  # 2) Tamanho do bloco para alternância
  block_size=$(( m / 2 ))
  if (( block_size < 1 )); then block_size=$total; fi

  # 3) Geração da sequência
  seq=()
  current=2
  for (( i=0; i<total; i++ )); do
    # alterna a cada block_size
    if (( i > 0 && i % block_size == 0 )); then
      current=$(( current == 2 ? 0 : 2 ))
    fi

    # chance muito baixa de gerar um 1
    if (( RANDOM % 1000 == 0 )); then
      val=1
    else
      val=$current
    fi

    seq+=( "$val" )
  done

  # 4) Gera entrada.txt
  {
    echo "$m $n"
    echo "${seq[@]}"
    echo "0 0"
  } > entrada.txt

  entrada=$(<entrada.txt)

  # 5) Executa tp1 com e sem -f
  ./tp1 -i entrada.txt -o saida.txt -f 2
  out1=$(<saida.txt)

  ./tp1 -i entrada.txt -o saida.txt -f 1
  out2=$(<saida.txt)

  # 6) Compara
  if [[ "$out1" != "$out2" ]]; then
    echo "Incorreto para a entrada:"
    echo "$entrada"
    exit 1
  else
    echo "Correto"
  fi
done