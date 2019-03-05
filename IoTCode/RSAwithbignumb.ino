#include <BigNumber.h>
//bool operator== (const BigNumber & rhs) const;

BigNumber modInverse(BigNumber,BigNumber);

void setup ()
{
  Serial.begin (115200);
  BigNumber::begin ();

  /////////// SIMPLE KEY GENERATION EXMAPLE ///////////////////
  BigNumber p = "12131072439211271897323671531612440428472427633701410925634549312301964373042085619324197365322416866541017057361365214171711713797974299334871062829803541";
  BigNumber q = "12027524255478748885956220793734512128733387803682075433653899983955179850988797899869146900809131611153346817050832096022160146366346391812470987105415233";
  BigNumber n = p*q; //RSA 1024
  Serial.print("The public key (n) is equal to : ");Serial.println(n);
  BigNumber e = "65537";
  BigNumber phi = (p-"1")*(q-"1"); //øhhh, det virkede ikke lige med normal et'ere men burde virke nu 
  Serial.print("The phi function is equal to   : ");Serial.println(phi);

  BigNumber d = modInverse(e,phi);
  Serial.print("The modular inverse is equal to: ");
  Serial.println(d);



/*
  //////////////// SIMPLE ENCRYPTION EXAMPLE ////////////////////
  BigNumber m = 72; //what we want to send! which is 'H' in ascii
  //BigNumber me = (m.pow(e)) % n; //CIPHER TEXT (what the 'attacker' sees)
  BigNumber me = m.powMod (e,n); //test which method is fastest. 
  Serial.print ("The cipher text is equal to:  "); 
  Serial.println(me); 
  //Receiver then calculates: ((decryption))
  //BigNumber cd = (me.pow(d)) %n;
  BigNumber cd = me.powMod(d,n);
  Serial.println("The receiver has received: ");
  Serial.println(cd);
 */
}

void loop () { }

BigNumber modInverse(BigNumber a, BigNumber m) 
{ 
    a = a%m; 
    for (BigNumber i=1; i<m; i++){
      if ((a*i) % m == 1){ //m.powMod (e,n); //test which method is fastest. 
        return i;
      }
    }
    
} 
