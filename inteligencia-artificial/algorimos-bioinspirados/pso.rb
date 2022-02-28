# Este algoritmo maximiza uma função do tipo ax² + bx + c.
# Utilizaremos a Otimização de enxame de partículas para tal.
class PsoAlgorithm

  attr_reader :a, :b, :c, :w, :c1, :c2, :r1, :r2, :n, :g_best_fitness, :iterations,
              :p_best, :g_best, :particles, :velocity, :example, :fitness, :last_fitness

  # Por default, utilizaremos a função vista em aula: f(x) = -X² + 2X + 1

  def initialize(a: -1, b: 2, c: 1, w: 0.7, c1: 0.20, c2: 0.60, r1: 0.4657, r2: 0.5319, n: 5, iterations: 10)
    # Constantes da função f(x)
    @a, @b, @c = a, b, c

    # Constantes da nossa função de velocidade
    @w, @c1, @c2, @r1, @r2 = w, c1, c2, r1, r2

    # Número de partículas
    @n = n
    
    # Conjunto de partículas e vetor de melhor desempenho local destas
    @particles = @p_best = Array.new 

    # Vetor de velocidade, fitness, e um vetor para armazenar os valores de fitness anterior 
    @velocity = @fitness = @last_fitness = Array.new

    # Párticula com o melhor desempenho global e seu fitness
    @g_best = @g_best_fitness = 0

    # Número de iterações que iremos realizar, por default é 10
    @iterations = iterations
  end

  def self.perform(*args)
    new(*args).perform
  end

  # Todas as ações do código estão explícitas no método perform
  def perform
    generate_particles
    generate_particles_velocity
    vary_particles_values
    vary_velocity_values
    set_local_best_position

    iterations.times do |index|
      apply_velocity_function unless index.zero?
      update_fitness_function
      update_global_best_position
      update_local_best_position      
      set_last_fitness
      print_results(index+1)
    end
  end

  private

  # Define inicialmente nosso p_best, que será as próprias partículas
  def set_local_best_position
    @p_best = particles
  end

  # Gera as N partículas com valores aleatórios
  def generate_particles
    n.times { particles.push(rand().round(4)) }
  end

  # Varia os valores gerados subtraindo 0.5 e multiplicando por 10
  def vary_particles_values
    @particles = @particles.map{ |particle| (10*(particle-0.5)).round(4) }
  end

  # Gera as N velocidades de cada uma das partículas
  def generate_particles_velocity
    n.times { velocity.push(rand().round(4)) }
  end

  # Varia os valores gerados subtraindo 0.5
  def vary_velocity_values
    @velocity = @velocity.map{ |velocity| (velocity-0.5).round(4) }
  end

  # Atualiza a função de fitness pra cada uma das partículas
  def update_fitness_function
    @fitness = @particles.map{ |particle| evaluation_function(particle) }
  end

  # Atualiza, se necesário, o melhor desempenho global (g_best)
  def update_global_best_position
    # Verificamos qual o melhor valor de fitness da iteração
    local_best_fitness = @fitness.sort.last
    possible_g_best = nil

    # Buscamos este valor na posição adequada no array de partículas
    n.times do |i| 
      possible_g_best = particles[i] if @fitness[i] == local_best_fitness
    end
    
    # Caso o valor seja maior que o valor atual, atualizamos g_best e seu fitness
    if local_best_fitness > @g_best_fitness
      @g_best = possible_g_best 
      @g_best_fitness = local_best_fitness
    end
  end

  # Atualiza o vetor p_best nas posições adequadas
  def update_local_best_position
    n.times do |i|
      @p_best[i] = @particles[i]  if @last_fitness[i].nil? || @fitness[i] > @last_fitness[i]
    end
  end

  # Definine a função de fitness da iteração anterior
  def set_last_fitness
    @last_fitness = @fitness
  end

  # Função de avaliação
  def evaluation_function(x)
    # ax² + bx + c
    (a*(x**2) + b*(x) + c).round(4)
  end

  # Aplica a função de velocidade em cada uma das partículas
  def apply_velocity_function
    particles.each_with_index do |particle, i|
      particles[i] = (particles[i] + velocity_function(i, particle)).round(4)
    end
  end

  # Função de velocidade
  def velocity_function(i, particle)
    # Vi+1 = WVi + C1R1 (Pbest - Xi) + C2R2 (Gbest - Xi)
    velocity[i] = (w*velocity[i] + (c1*r1 * (p_best[i] - particle)) + (c2*r2 * (g_best - particle))).round(4)
  end

  # Imprime a cada iteração o resultado parcial encontrado
  def print_results(index)
    puts "Iteração #{index}:"
    puts ""
    puts "Velocidade (V): " << velocity.inspect
    puts "Partículas (X): " << particles.inspect
    puts "Fitness    (F): " << @fitness.inspect
    puts "P Best        : " << p_best.inspect
    puts "G Best fitness: " << g_best_fitness.to_s
    puts "G Best        : " << g_best.to_s
    puts ""
    puts ""
  end
end
