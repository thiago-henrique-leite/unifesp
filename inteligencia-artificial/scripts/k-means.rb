class KMeans
  attr_reader :a1_values, :a2_values, :k, :prototypes, :groups

  def initialize(k:3, prototypes:nil, a1_values:nil, a2_values:nil)
    @k = k
    @prototypes = set_prototypes(prototypes)
    @a1_values = set_a1_values(a1_values)
    @a2_values = set_a2_values(a2_values)
  end

  def self.perform(*args)
    new(*args).perform
  end
  
  def perform
    while !is_balanced?
      reset_groups
      assign_objects
      print_groups
      centroids unless is_balanced?
    end
    
    print_result
  end

  private
  
  def set_a1_values(a1)
    a1.nil? ? [1, 2, 1, 2, 8, 9, 9, 8, 1, 2, 1, 2] : a1
  end
  
  def set_a2_values(a2)
    a2.nil? ? [2, 1, 1, 2, 9, 8, 9, 8, 15, 15, 14, 14] : a2
  end
  
  def set_prototypes(prototypes)
    prototypes.nil? ? [[6,6], [4,6], [5,10]] : prototypes
  end

  def reset_groups
    @groups = []
  
    k.times {|i| @groups << Array.new}
  end
  
  def is_balanced?
    return false if groups.nil?
    
    elements_by_group = []
    groups.map{ |group| elements_by_group << group.size }
    elements_by_group.uniq.size == 1 && !elements_by_group.last.zero?
  end

  def euclidean_distance(i, prototype)
    Math::sqrt(((prototype[0] - a1_values[i]) ** 2) + ((prototype[1] -a2_values[i]) ** 2))
  end

  def assign_objects
    puts ""
    puts "Calculando distâncias e agrupando os pontos.."
    puts ""

    a1_values.size.times do |i|
      shortest_distance = euclidean_distance(i, prototypes[0])

      group_id = 0
      
      print shortest_distance.round(2).to_s + " | "

      for j in 1...k do
        distance = euclidean_distance(i, prototypes[j])
        
        print distance.round(2).to_s + " | "
        
        if distance < shortest_distance
          shortest_distance = distance
          group_id = j
        end
      end
      
      puts ""
      
      groups[group_id] << [a1_values[i], a2_values[i]]
    end
  end

  def centroids
    puts ""
    puts "Redefinindo os protótipos.."
    puts ""
    
    groups.each_with_index do |group, index|
      prototypes[index][0] = media(group, 0)
      prototypes[index][1] = media(group, 1)
    end
  
    puts "Novos protótipos: #{prototypes.inspect}"
    puts ""
  end
  
  def media(group, index)
    sum = 0
    
    group.each do |point|
      sum += point[index]
    end
    
    media = (sum.to_f / group.size).round(2)
  end

  def print_groups
    puts ""
    groups.each_with_index do |group, i|
      puts "Grupo [#{i}]: #{group.inspect}"
    end
  end

  def print_result
    puts ""
    puts "Algoritmo KMeans encerrado!"
    puts ""
    puts "Protótipos finais: #{prototypes.inspect}"
    puts ""
    puts "Grupos finais: "
    print_groups
    puts ""
  end
end
