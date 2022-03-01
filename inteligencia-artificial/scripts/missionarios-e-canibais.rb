State = Struct.new(:m_left, :c_left, :m_rigth, :c_rigth, :boat_dir, :m, :c) do
  def left?
    boat_dir == :left
  end

  def rigth?
    boat_dir == :rigth
  end

  def isValid?(miss, can)
    (more_miss_than_can? || m_left.zero? || m_rigth.zero?) && correct_sum?(miss, can) && positive_values?
  end

  def isFinal?(missionaries, cannibals)
    m_left == missionaries && c_left == cannibals
  end

  def more_miss_than_can?
    m_left >= c_left && m_rigth >= c_rigth
  end

  def correct_sum?(miss, can)
    m_left + m_rigth == miss && c_left + c_rigth == can
  end

  def positive_values?
    c_left >= 0 && c_rigth >= 0 && m_left >= 0 && m_rigth >= 0
  end
end

class MissionariosECanibais

  attr_reader :inicial_state, :pending_states, :checked_states, :boat_capacity, 
              :missionaries, :cannibals, :solve

  def initialize(missionaries: 3, cannibals: 3, boat_capacity: 2)
    @missionaries = missionaries
    @cannibals    = cannibals
    @boat_capacity  = boat_capacity
    @pending_states = []
    @checked_states = []
    @solve = []
  end

  def self.play(*args)
    new(*args).play
  end

  def play
    define_inicial_state
    final_state = breadth_first_search
    finish_game(final_state)
  end

  private

  def define_inicial_state
    puts @inicial_state = State.new(0, 0, missionaries, cannibals, :rigth, 0, 0)
    
    puts "\nINÍCIO > #{cannibals} Canibais e #{missionaries} Missionários na margem direita!\n\n"
    
    raise 'Invalid Inicial State!' if cannibals > missionaries
  end

  def breadth_first_search    
    pending_states.push(inicial_state)
    previous = inicial_state
    
    while pending_states.any?
      state = pending_states.pop
      register_action(state, previous)
      previous = state

      return state if state.isFinal?(missionaries, cannibals)
      checked_states.push(state)

      sons = successors(state, previous)
      sons.each { |son| pending_states.push(son) if exclude?(checked_states, son) && exclude?(pending_states, son) }
    end
  end

  def exclude?(array, son)
    array.each { |state| return false if isEqual?(state, son) } 
    true
  end

  def isEqual?(x, y)
    x.m_left == y.m_left && x.m_rigth == y.m_rigth && x.c_left == y.c_left && x.c_rigth == y.c_rigth && x.boat_dir == y.boat_dir
  end

  def successors(state, previous)
    successors = Array.new

    if missionaries+cannibals <= @boat_capacity
      return [State.new(state.m_left+missionaries, state.c_left+cannibals, state.m_rigth-missionaries, state.c_rigth-cannibals, :left)]
    end

    (@boat_capacity+1).times do |i|
      (@boat_capacity+1).times do |j|
        next if i.zero? && j.zero? || i+j > @boat_capacity
        
        if state.rigth?
          new_state = State.new(state.m_left+i, state.c_left+j, state.m_rigth-i, state.c_rigth-j, :left, i, j)
        else
          new_state = State.new(state.m_left-i, state.c_left-j, state.m_rigth+i, state.c_rigth+j, :rigth, i, j)
        end

        successors << new_state if new_state.isValid?(missionaries, cannibals) && !isEqual?(new_state, previous)
      end
    end
    
    successors
  end

  def register_action(state, previous)
    return if state.equal?(inicial_state)

    can       = (state.c.zero?) ? '' : "#{state.c} canibal(is)"
    miss      = (state.m.zero?) ? '' : "#{state.m} missionário(s)"
    direction = (state.left?) ? "esquerda." : "direita."

    solve.pop if state.left? && previous.left? || state.rigth? && previous.rigth?

    if can.empty? || miss.empty?
      solve << "Mova => #{can}#{miss} para #{direction}" 
    else 
      solve << "Mova => #{can} e #{miss} para #{direction}"
    end
    
    if state.isFinal?(missionaries, cannibals)
      solve << "\nFIM > #{state.c_left} Canibais e #{state.m_left} Missionários na margem esquerda!\n\n" 
    end
  end

  def finish_game(final_state)
    if solve.last.split.first == 'FIM'
      solve.each { |action| puts action }
    else
      puts "\nÉ impossível concluir o jogo com os parâmetros fornecidos!" 
    end

    final_state
  end
end
