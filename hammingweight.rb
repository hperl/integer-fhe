require 'rubygems'
require 'symbolic'

def symb_hamming(a)
  s1 = a.count
  result = Array.new(4, 0)
  
  1.upto(s1) do |i|
    i # => 
    [i, 4].min.downto(2) do |k|
      k # =>  # !> discarding old **
      result[k-1] = result[k-1] + result[k-2] * a[i-1]
    end
    result[0] = result[0] + a[i-1]
  end
  result # !> `&' interpreted as argument prefix
end

puts symb_hamming([1,0,1,0,1])
