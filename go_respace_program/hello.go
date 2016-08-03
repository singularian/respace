package main

import (
//	"encoding/binary"
	"fmt"
//	"strings"
	"math/rand"
)

// calculate the number of iterations
// should return integer
func calcIterations(text string) (uint64) {
        size := 0;
        size = len(text)
	count := 0;
	for i := size; i > 0; i--  {
		count = count + i
	}
	fmt.Println("Value of count is now:", count)
	return uint64(count)
}

// calculate the number of iterations
// should return integer
func calcIterationsLength(text string) (uint64) {
        size := 0;
        size = len(text)
        count := 0;
        for i := size; i > 0; i--  {
		for j := i; j < size; j++ {
                count = count + j
		}
        }
        fmt.Println("Value of count is now:", count)
        return uint64(count)
}


// pyramid parser
// I installed the sql lite interface for go
// add an optimization to maybe check only n sized strings for the j part
func pyramidScan(text string) (string) {
	var result []byte
        var str = "";
	count := 0;
	size := 0;
        size = len(text)
        size = size - 1
        end := size + 1 
	for i := 0; i <= size; i++  {
	//  	for j := end; j >= 0; j--  {
	  	for j := i; j <= end; j++  {
        // fmt.Println(x)
    	// var bstr = "testing"
    	// str = str[:len(str)-1]
    	// bstr = str[1:3]
    	// p("testing", str, bstr)
			var substring = text
			total := i + j
        		if i != j {
			str = substring[i:j]
			count++
			// fmt.Println("Value of i,j is now:", size, total, count, i, j, str)
			fmt.Println("Value of i,j is now:", i, j, count, total,  str)
			}
		}
	}

	return string(result) // f will be closed if we return here.
}


func main() {
    fmt.Printf("hello, world\n")
    fmt.Println("My favorite number is", rand.Intn(10))
    // calcIterationsLength("TheWorldisFlat.")
    // calcIterations("TheWorldisFlat.")
    // pyramidScan("TheWorldisFlat.")
    calcIterations("TheWorldisFlat.12354.Howisthisname?Ishetheone?Whoareyou?Isheblind?")
    calcIterationsLength("TheWorldisFlat.12354.Howisthisname?Ishetheone?Whoareyou?Isheblind?")
    pyramidScan("TheWorldisFlat.12354.Howisthisname?Ishetheone?Whoareyou?Isheblind?")
}
