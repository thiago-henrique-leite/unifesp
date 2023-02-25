class AcoAlgorithm
  ITERATIONS = 100
  MATRIX_DIMENSION = 8
  ALPHA = 1
  BETA = 1
  RHO = 0.1
  DISTANCES = {
    '01' => 42,
    '02' => 61,
    '03' => 30,
    '04' => 17,
    '05' => 82,
    '06' => 31,
    '07' => 11,
    '12' => 14,
    '13' => 87,
    '14' => 28,
    '15' => 70,
    '16' => 19,
    '17' => 33,
    '23' => 20,
    '24' => 81,
    '25' => 21,
    '26' => 8,
    '27' => 29,
    '34' => 34,
    '35' => 33,
    '36' => 91,
    '37' => 10,
    '45' => 41,
    '46' => 34,
    '47' => 82,
    '56' => 19,
    '57' => 32,
    '67' => 59
  }.freeze

  attr_reader :pheromone_matrix, :edge_quality, :probabilities, :visited_vertexs, :best_solutions, :best_fitness

  def initialize
    @current_iteration = 0
    @edge_quality = []
    @best_fitness = []
    @probabilities = []
    @best_solutions = []
    @visited_vertexs = []
    @pheromone_matrix = []
  end

  def self.perform
    new.perform
  end

  def perform
    build_pheromone_matrix_and_edge_quality

    ITERATIONS.times do |index|
      initial_vertex = index % MATRIX_DIMENSION

      build_path(initial_vertex)
      update_best_solutions(initial_vertex)
    end

    solutions_fitness = best_solutions.zip(best_fitness).to_h

    bestest_path = solutions_fitness.min_by { |_, v| v }

    print_path(bestest_path[0], bestest_path[1])
  end

  def build_pheromone_matrix_and_edge_quality
    MATRIX_DIMENSION.times do |i|
      pheromone_matrix[i] = []
      edge_quality[i] = []

      MATRIX_DIMENSION.times do |j|
        pheromone_matrix[i][j] = 1
        edge_quality[i][j] = DISTANCES[[i, j].sort.join] || 0
      end
    end
  end

  def build_path(vertex)
    @probabilities = []
    @visited_vertexs = [vertex]

    calculate_probabilities(vertex)

    (MATRIX_DIMENSION - 1).times do
      define_next_vertex

      calculate_probabilities(visited_vertexs.last)
    end

    update_pheromone(vertex)
  end

  def calculate_probabilities(vertex)
    MATRIX_DIMENSION.times do |index|
      probabilities[index] =
        visited_vertexs.include?(index) ? 0 : probability_function(vertex, index)
    end
  end

  def update_pheromone(vertex)
    MATRIX_DIMENSION.times do |index|
      next if index == vertex

      pheromone_matrix[vertex][index] = calculate_new_pheromone(vertex, index).round(2)
    end
  end

  def define_next_vertex
    max_prob = probabilities.max

    probabilities.each_with_index do |prob, next_vertex|
      next if prob != max_prob

      @visited_vertexs << next_vertex

      break
    end
  end

  def probability_function(origin, target)
    ALPHA * pheromone_matrix[origin][target].to_f * BETA * 1 / edge_quality[origin][target].to_f
  end

  def calculate_new_pheromone(origin, target)
    (1 - RHO) * pheromone_matrix[origin][target].to_f + 0.5 * 1 / edge_quality[origin][target].to_f
  end

  def update_best_solutions(vertex)
    vertex_fitness = fitness(visited_vertexs)

    return unless best_solutions[vertex].nil? || vertex_fitness < best_fitness[vertex]

    best_solutions[vertex] = visited_vertexs
    best_fitness[vertex] = vertex_fitness
  end

  def fitness(road)
    format_road(road).sum { |trip| DISTANCES[trip] }
  end

  def format_road(road)
    rotated_road = road.dup
    rotated_road << rotated_road.shift

    road.zip(rotated_road).map(&:sort).map(&:join)
  end

  def print_path(path, fitness)
    letters = Array('A'..'H')

    path.each do |vertex|
      print "#{letters[vertex]} -> "
    end

    puts " | Fitness: #{fitness}"
  end
end

AcoAlgorithm.perform
