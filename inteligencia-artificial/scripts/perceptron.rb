class Perceptron
  CHECK = "\e[0;32m✓\e[m"
  WRONG = "\e[0;31m✗\e[m"

  attr_reader :dataset, :bias, :taxa_aprendizagem, :testes, :pesos

  def initialize(dataset, bias, taxa_aprendizagem, pesos, testes)
    @dataset = dataset
    @bias = bias
    @taxa_aprendizagem = taxa_aprendizagem
    @testes = testes
    @pesos = pesos
  end

  def self.perform(*args)
    new(*args).perform
  end

  def perform
    definir_peso_limiar
    treinar_algoritmo
    classificar_casos_teste
  end

  private

  def definir_peso_limiar
    pesos.unshift(-bias)
  end

  def treinar_algoritmo
    puts ''
    puts 'Treinando data set...'
    puts ''
    puts 'Pesos Iniciais: ' + pesos.inspect
    puts ''

    until convergiu? do
      puts ''
      puts 'Atualizando pesos...'
      
      classe, saida, classe_esperada = nil
      
      dataset.each do |individuo|
        saida = funcao_de_ativacao(individuo)
        classe = definir_classe_pela_saida(saida)
        atualizar_pesos(individuo, classe, individuo.last)
        puts 'Pesos: ' + pesos.inspect
      end
    end
  end

  def convergiu?
    puts ''
    puts 'Analisando convergência...'

    for i in 0...(dataset.size)
      saida = funcao_de_ativacao(dataset[i])

      caso_teste     = dataset[i].first
      saida_esperada = dataset[i].last
      saida_obtida   = definir_classe_pela_saida(saida)
      
      imprime_resultado(caso_teste, saida_obtida, saida_esperada)

      return false if saida_esperada != saida_obtida 
    end

    true
  end

  def definir_classe_pela_saida(saida)
    (saida < 0) ? -1 : +1 
  end

  def imprime_resultado(caso_teste, saida_obtida, saida_esperada)
    puts "\t#{caso_teste}: #{(saida_esperada == saida_obtida) ? CHECK : WRONG}"
  end

  def atualizar_pesos(individuo, classe_obtida, classe_esperada)
    return if classe_obtida == classe_esperada

    pesos.size.times do |i|
      valor = (i.zero?) ? 1 : individuo[i]

      @pesos[i] = pesos[i] + delta_peso(valor, classe_obtida, classe_esperada)
      @pesos[i] = pesos[i].round(2)
    end
  end

  def delta_peso(valor, classe_obtida, classe_esperada)
    taxa_aprendizagem * valor * (classe_esperada - classe_obtida)
  end

  def funcao_de_ativacao(individuo)
    saida = pesos.first

    for i in 1...(pesos.size)
      saida = saida + pesos[i]*individuo[i]
    end
    
    saida.round(2)
  end

  def classificar_casos_teste
    puts ''
    puts 'Executando testes...'
    puts ''

    testes.each do |teste|
      saida = funcao_de_ativacao(teste)
      classe = definir_classe_pela_saida(saida)
      puts("#{teste.first} => Saída: #{saida} | Classe: #{classe}")
    end

    puts ''
  end
end

Perceptron.perform([['A',0,0,1,-1], ['B',1,1,0,1]], 0.5, 0.4, [+0.4, -0.6, +0.6], [['TesteA',1,1,1],['TesteB',0,0,0]])

entrada = [
  ['João' , 1, 1, 0,	1, -1],
  ['Pedro', 0, 0, 1,	0, +1],
  ['Maria', 1, 1, 0,	0, +1],
  ['José' , 1, 0, 1,	1, -1],
  ['Ana'  , 1, 0, 0,	1, +1],
  ['Leila', 0, 0, 1,	1, -1]
]

testes = [["Luis", 0, 0, 0, 1], ["Laura", 1, 1, 1, 1]]

Perceptron.perform(entrada, -0.5, 0.5, [0, 0, 0, 0], testes)
