class CryptByte
  attr_reader :value, :original
  
  def CryptByte.encrypt(val, p)
    CryptByte.new(val + rand(100) * p, val)
  end

  def initialize(val, original = nil)
    @value = val
    @original = original
  end
  
  def decrypt(p)
    @value.modulo p
  end
  
  def +(other)
    CryptByte.new(@value + other.value, @original + other.original)
  end
  
  def *(other)
    CryptByte.new(@value * other.value, @original * other.original)
  end
end

a = CryptByte.encrypt(4, 23)      # => #<CryptByte:0x10014fbf8 @value=901, @original=4>
b = CryptByte.encrypt(5, 23)      # => #<CryptByte:0x10014f540 @value=419, @original=5>
c = CryptByte.encrypt(3, 23)      # => #<CryptByte:0x10014eeb0 @value=2027, @original=3>

3.times { c = c * b }
c                                 # => #<CryptByte:0x10014e7a8 @value=149106239593, @original=375>
c.decrypt(23)                      # => 7
