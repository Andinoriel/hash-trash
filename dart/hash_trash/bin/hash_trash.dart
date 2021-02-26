import 'package:ansicolor/ansicolor.dart';
import 'package:hash_trash/hash_trash.dart';

void main(List<String> arguments) {
  ansiColorDisabled = false;
  var X = getRandomX(length: 19);
  var Y = <int>[];
  for (var i = 0; i < X.length; i++) {
    Y.add(X[i] ^ 1 << i);
  }
  var binsX = <String>[];
  var binsY = <String>[];
  var hashX = <int>[];
  var hashY = <int>[];
  for (var x in X) {
    binsX.add(x.toRadixString(2).padLeft(20, '0'));
    hashX.add(getHash(value: x));
  }
  for (var y in Y) {
    binsY.add(y.toRadixString(2).padLeft(20, '0'));
    hashY.add(getHash(value: y));
  }
  var collisionsHashX = countCollisions(hashX);
  var collisionsHashY = countCollisions(hashY);
  var collisionBetweenHashXY = countCollisionBetween(hashX, hashY);
  print('X:');
  for (var i = 0; i < hashX.length; i++) {
    print(getOutputLine(
        left: X[i],
        binLeft: binsX[i],
        binRight: binsY[i],
        collisions: collisionsHashX,
        hashLeft: hashX[i],
        hashRight: hashY[i]));
  }
  print('Y:');
  for (var i = 0; i < hashY.length; i++) {
    print(getOutputLine(
        left: Y[i],
        binLeft: binsY[i],
        binRight: binsX[i],
        collisions: collisionsHashY,
        hashLeft: hashY[i],
        hashRight: hashX[i],
        hashCheck: true));
  }
  print('Correlation coefficient (X, HASH X): ' +
      correlationCoefficient(x: X, y: hashX).toStringAsFixed(2));
  print('Correlation coefficient (Y, HASH Y): ' +
      correlationCoefficient(x: Y, y: hashY).toStringAsFixed(2));
  print('Correlation coefficient (HASH X, HASH Y): ' +
      correlationCoefficient(x: hashX, y: hashY).toStringAsFixed(2));
  print('Correlation coefficient (X, Y): ' +
      correlationCoefficient(x: X, y: Y).toStringAsFixed(2));
  print('Collision in H(X). Collision pairs: ${collisionsHashX.length}');
  print('Collision in H(Y). Collision pairs: ${collisionsHashY.length}');
  print('Collision between H(X) and H(Y). Collision pairs: ' +
      collisionBetweenHashXY.length.toString());
}
