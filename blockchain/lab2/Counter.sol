// Counter.sol
pragma ton-solidity >=0.39.0;
pragma AbiHeader pubkey;

contract Counter {
    int256 private value;

    constructor(int256 initial, uint256 pubKey) public {
        require(msg.pubkey() == pubKey, 101);
        tvm.accept();
        value = initial;
    }

    // increment by 1
    function increment() public {
        require(msg.pubkey() == tvm.pubkey(), 102);
        tvm.accept();
        value += 1;
    }

    // decrement by 1
    function decrement() public {
        require(msg.pubkey() == tvm.pubkey(), 103);
        tvm.accept();
        value -= 1;
    }

    // getter (read-only)
    function getValue() public view returns (int256) {
        return value;
    }
}
