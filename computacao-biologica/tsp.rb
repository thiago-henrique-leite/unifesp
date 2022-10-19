# frozen_string_literal: true

# Traveling Salesman Problem (TSP) using Genetic Algorithm
class TSP
  GENERARION_SIZE = 50
  MAX_GENERARIONS = 400

  DISTANCES = {
    'AB' => 42,
    'AC' => 61,
    'AD' => 30,
    'AE' => 17,
    'AF' => 82,
    'AG' => 31,
    'AH' => 11,
    'BC' => 14,
    'BD' => 87,
    'BE' => 28,
    'BF' => 70,
    'BG' => 19,
    'BH' => 33,
    'CD' => 20,
    'CE' => 81,
    'CF' => 21,
    'CG' => 8,
    'CH' => 29,
    'DE' => 34,
    'DF' => 33,
    'DG' => 91,
    'DH' => 10,
    'EF' => 41,
    'EG' => 34,
    'EH' => 82,
    'FG' => 19,
    'FH' => 32,
    'GH' => 59
  }.freeze

  attr_reader :curr_generation, :next_generation, :generation_fitness, :bestest_individual

  def initialize
    @curr_generation = []
    @next_generation = []
    @generation_fitness = {}
    @crossover_size = 0
    @unchanged_size = 0
    @mutations_size = 0
    @generation_index = 0
    @generations_with_best_unchanged = 0
  end

  def self.perform
    new.perform
  end

  def perform
    generate_initial_population

    MAX_GENERARIONS.times do
      @generation_index += 1

      produce_next_generation

      break if generations_with_best_unchanged >= 100
    end

    track_metrics
  end

  private

  attr_reader :crossover_size, :unchanged_size, :mutations_size, :generation_index, :generations_with_best_unchanged

  def generate_initial_population
    base_individual = %w[A B C D E F G H]

    GENERARION_SIZE.times do
      @curr_generation << format_individual(base_individual.shuffle)
    end

    @bestest_individual = curr_generation[0]
  end

  def format_individual(individual)
    rotated_individual = individual.dup
    rotated_individual << rotated_individual.shift

    individual.zip(rotated_individual).map(&:sort).map(&:join)
  end

  def produce_next_generation
    @next_generation = []

    curr_generation_individuals = sort_individuals_by_fitness

    update_bestest_individual(curr_generation_individuals[0])

    @next_generation << curr_generation_individuals[0]
    @next_generation << curr_generation_individuals[1]

    curr_generation_individuals.shift
    curr_generation_individuals.shift

    reproduce_individuals(curr_generation_individuals.shuffle)

    @curr_generation = next_generation
  end

  def update_bestest_individual(candidate)
    bestest_individual_fitness = fitness(bestest_individual)
    candidate_fitness = fitness(candidate)

    if candidate_fitness < bestest_individual_fitness
      @bestest_individual = candidate
      @generations_with_best_unchanged = 0
    else
      @generations_with_best_unchanged += 1
    end
  end

  def sort_individuals_by_fitness
    @generation_fitness = {}

    curr_generation.each do |individual|
      @generation_fitness[individual] = fitness(individual)
    end

    generation_fitness.sort_by { |_, value| value }.map(&:first)
  end

  def fitness(individual)
    individual.sum { |trip| DISTANCES[trip] }
  end

  def reproduce_individuals(individuals)
    number_of_couples = individuals.size / 2

    index = 0

    number_of_couples.times do
      father = individuals[index]
      mother = individuals[index + 1]

      cross(father, mother)

      index += 2
    end
  end

  def cross(mother, father)
    ticket = rand(1..100)

    formatted_mother = mother.join.chars.uniq
    formatted_father = father.join.chars.uniq

    return to_crossover(formatted_mother, formatted_father) if ticket >= 0 && ticket <= 75
    return keep_parents(formatted_mother, formatted_father) if ticket > 75 && ticket <= 95

    mutate(formatted_mother, formatted_father)
  end

  def to_crossover(mother, father)
    @crossover_size += 1

    child1 = mother.zip(father).shuffle.flatten.uniq
    child2 = father.zip(mother).shuffle.flatten.uniq

    add_childs(child1, child2)
  end

  def keep_parents(mother, father)
    @unchanged_size += 1

    add_childs(mother, father)
  end

  def mutate(mother, father)
    @mutations_size += 1

    child1 = mother.join.chars.uniq.shuffle
    child2 = father.join.chars.uniq.shuffle

    add_childs(child1, child2)
  end

  def add_childs(child1, child2)
    @next_generation << format_individual(child1)
    @next_generation << format_individual(child2)
  end

  def track_metrics
    st_place = curr_generation[0].sort
    nd_place = curr_generation[1].sort

    cross_size = crossover_size + unchanged_size + mutations_size

    crossover_percent = (crossover_size * 100 / cross_size.to_f).round(2)
    unchanged_percent = (unchanged_size * 100 / cross_size.to_f).round(2)
    mutations_percent = (mutations_size * 100 / cross_size.to_f).round(2)

    puts ""
    puts "Resultados após #{generation_index} gerações de #{GENERARION_SIZE} indivíduos!"
    puts ""
    puts "Realizou Crossover..: #{crossover_percent}%"
    puts "Manteve os Pais.....: #{unchanged_percent}%"
    puts "Realizou Mutação....: #{mutations_percent}%"
    puts ""
    puts "1º: #{st_place} | Fitness: #{fitness(st_place)}"
    puts "2º: #{nd_place} | Fitness: #{fitness(nd_place)}"
    puts ""
  end
end

TSP.perform
