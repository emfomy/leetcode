struct Solution {
  static inline int data;
  static void init() {  //
    data = 1;
  }
  static inline const bool initialized = (init(), true);
};
