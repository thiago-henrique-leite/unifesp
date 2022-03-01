class AcoAlgorithm

  attr_reader :initial_vertex, :pheromone_matrix, :edge_quality, :probabilities, :matrix_dimension,
              :initial_pheromone_value, :visited_vertices, :alpha, :beta, :rho, :default_edge_quality

  def initialize(
    matrix_dimension: 5, 
    initial_pheromone_value: 2, 
    alpha: 1, 
    beta: 1, 
    rho: 0.5, 
    default_edge_quality: true,
    imprint_pheromone_matrix: true
  )
    @initial_pheromone_value = initial_pheromone_value
    @matrix_dimension = matrix_dimension
    @initial_vertex   = 0
    @pheromone_matrix = []
    @edge_quality     = []
    @probabilities    = []
    @visited_vertices = []

    # Constantes utilizadas
    @alpha = alpha
    @beta  = beta
    @rho   = rho

    # Define se queremos utilizar os valores padrão
    @default_edge_quality = default_edge_quality

    # Define se deverá ser impressa a matriz de feromônio durate a execução
    @imprint_pheromone_matrix = imprint_pheromone_matrix
  end

  def self.perform(*args)
    new(*args).perform
  end

  def perform
    build_pheromone_matrix
    
    (default_edge_quality) ? define_default_edge_quality : build_edge_quality
        
    matrix_dimension.times do |i|
      define_caminhos(i)
      print_pheromone_matrix if @imprint_pheromone_matrix
    end
  end

  # Iniciamos a matriz de feronômios com 2 para todo elemento A[i][j], i!=j
  def build_pheromone_matrix
    matrix_dimension.times do |i|
      pheromone_matrix.push([])
      matrix_dimension.times do |j|
        pheromone_matrix[i][j] = (i==j) ? 0 : initial_pheromone_value
      end
    end
  end

  # Define a qualidade da aresta
  # Valores fixos conforme o exemplo do exercício
  def build_edge_quality
    matrix_dimension.times do |i|
      edge_quality.push([])
      matrix_dimension.times do |j|
        print "Digite a qualidade da aresta [#{i}][#{j}]: "
        while edge_quality[i][j].to_i <= 0
          edge_quality[i][j] = gets.chomp.to_i
        end
      end
    end
  end

  def define_default_edge_quality
    raise 'Dimensão da matriz deve ser igual a 5.' unless matrix_dimension == 5

    @edge_quality = [
      [0,  2, 10, 8, 3],
      [1,  0,  2, 5, 7],
      [9,  1,  0, 3, 6],
      [10, 4,  3, 0, 2],
      [2,  7,  5, 1, 0]
    ]
  end

  # Define o caminho dado o vértice inicial
  # Imprime o caminho gerado
  # Atualiza os feronomios 
  def define_caminhos(vi)
    print_initial_vertex(vi)

    @probabilities = []
    @visited_vertices = [vi]
    calculate_probabilities(vi)

    (matrix_dimension-1).times do |index|
      _next = define_next_vertex
      calculate_probabilities(_next)
    end

    print_path
    update_pheromone(vi)
  end

  # Imprime vértice inicial do novo caminho
  def print_initial_vertex(vi)
    puts("\nPartindo do vértice (#{translate_vertex(vi)})\n\n")
  end

  # Atualiza os feronômios do vértice inicial
  def update_pheromone(vi)
    matrix_dimension.times do |i|
      next if i == vi
      pheromone_matrix[vi][i] = calculate_new_pheromone(vi, i).round(2)
    end
  end

  # Calcula o novo valor do feronômio com a equação vista em aula
  def calculate_new_pheromone(vi, i)
    (1-rho)*pheromone_matrix[vi][i].to_f + 0.5 * (1/edge_quality[vi][i].to_f)
  end

  # Calcula a probabilidade para um vértice X visitar todos os outros vértices  
  def calculate_probabilities(initial_vertex)
    matrix_dimension.times do |index|
      if visited_vertices.include?(index)
        probabilities[index] = 0
      else
        probabilities[index] = probability_function(initial_vertex, index)
      end
    end
  end

  # Função de probabilidade de um vértice visitar outro
  def probability_function(vi, i)
    (((alpha.to_i*pheromone_matrix[vi][i].to_f)*(beta.to_i*(1/edge_quality[vi][i].to_f)))) / norm(vi, i)
  end

  # Define qual será o próximo vértice a ser visitado
  def define_next_vertex
    next_vertex = 0
    bigger_prob = probabilities.sort.last

    probabilities.each_with_index { |prob, i| next_vertex = i if prob == bigger_prob }
    
    visited_vertices.push(next_vertex)
    next_vertex
  end

  # Realiza o calculo do denomidar da normalização da função de probabilidade, por isto chamamos de norma
  def norm(vi, i)
    norm = 0
    matrix_dimension.times do |j|
      next if j == vi
      norm += pheromone_matrix[vi][j].to_f * (1/edge_quality[vi][j].to_f)
    end
    norm
  end

  # Traduz um número para uma letra 
  def translate_vertex(next_vertex)
    letters = ("A".."Z").to_a
    (next_vertex <= 26) ? letters[next_vertex] : next_vertex 
  end

  # Imprime o caminho realizado
  def print_path
    visited_vertices.each_with_index do |vertex, i|
      print (i<matrix_dimension-1) ? "#{translate_vertex(vertex)} => " : "#{translate_vertex(vertex)}\n"
    end
  end

  # Imprime a matriz de feronômios
  def print_pheromone_matrix
    puts ""
    pheromone_matrix.each do |line|
      pp line
    end
    puts ""
  end
end
