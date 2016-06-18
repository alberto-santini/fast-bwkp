#!/usr/bin/env ruby

require 'json'

@filename = ARGV[0]

inst = JSON.parse(File.read(@filename))

n = inst['n_items'];
q = inst['capacity'];
w = Array.new
p = Array.new
c = Array.new
nb = 0
nw = 0

inst['items'].each do |item|
  w << item['weight'].to_i
  p << item['prize'].to_i
  
  if item['colour'].to_i == 1
    nb += 1
    c << 'b'
  else
    nw += 1
    c << 'w'
  end
end

File.open(File.basename(@filename, '.json') + '.txt', 'w') do |f|
  f.puts "#{n} #{nb} #{nw} #{q}"
  f.puts c.join(' ')
  f.puts w.join(' ')
  f.puts p.join(' ')
end