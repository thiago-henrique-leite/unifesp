def prova_real(entrada_x, entrada_y)
  y_funcao_obtida, erro = [], []

  entrada_x.each_with_index do |x, i|
    # Função obtida pelo algoritmo de regressão linear
    y = (0.0087 * x + 2.4445).round(2) 

    # O erro é dado pela diferença do y esperado pelo y obtido
    erro << (entrada_y[i] - y).round(2) 

    # Salvamos o valor obtido na função encontrada 
    y_funcao_obtida << y
  end

  puts ""
  puts "Vetor de erros: #{erro.inspect}"
  puts ""
  puts "Maior erro obtido: #{erro.map(&:abs).sort.last}"
  puts ""
  puts "Erro médio: #{average(erro)}"
  puts ""
  puts "Valores de Y pela função: #{y_funcao_obtida.inspect}"
  puts ""
end

def average(array)
  soma_total = 0
  array.each{ |n| soma_total += n.abs }
  soma_total.to_f / array.size
end
