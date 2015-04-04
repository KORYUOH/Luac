-- sample.lua
--------------------------------------------------------------------------------

Name = "KORYUOH"

print("Hello, " .. Name .. "!")

print("CallTest")

Shout()
print (add(5,6))


--local Lib = require "Lib"

Mod.srand();

print( Mod.roll() );

print( Mod.tdice(2,3))

FB.FizzBuzz(15);
FB.FizzBuzzRoll();

function say()
	print ("He Saied " ..Name.. "")
end



function speech()
    print("Is your name " .. Name .. "?")
end

Destroyer()


function sum( x , y )
	print(""..x.. " + " ..y.. " = " ..x+y.."")
end

function power( x , y )
	sum = 1;
	for i = 0 , y do 
		sum = sum * x
	end
	print( "result = "..sum.."");
end
