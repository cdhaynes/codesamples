package oop.chaynes.hw6.one;
/**
 * Implements logic for Binary Search Trees
 *
 *
 * @author Casey Haynes
 * @class BinarySearchTree.java
 * @version HW6, #1
 * @bugs delete does not work properly
 */
import java.util.ArrayList;
import java.util.Comparator;

public class BinarySearchTree<E> {
    private Node root;

    private int size;

    private Comparator<E> comparator;

    public int getSize() {
        return size;
    }

    private class Node implements Comparator<E> {
        private E data;
        private Node left;
        private Node right;

        public Node(E data, Node left, Node right) {
            this.data = data;
            this.left = left;
            this.right = right;
        }

        public int compare(E a, E b) {
            return comparator.compare(a,b);
        }

        public void add(E data) {
            if (compare(data, this.data) <= 0) {
                if (this.left == null) {
                    Node n = new Node(data, null, null);
                    this.left = n;
                    size++;
                } else {
                    left.add(data);
                }
            } else if (compare(data, this.data) > 0) {
                if (this.right == null) {
                    Node n = new Node(data, null, null);
                    this.right = n;
                    size++;
                } else {
                    right.add(data);
                }
            }
        }

        public void remove(E data, Node parent) { /* may or may not work */
            if (compare(parent.data, data) == 0) {
                if (parent.left == null && parent.right == null) {
                    if (parent == root) {
                        parent  = null;
                    }
                    if (compare(parent.data, data) > 0) {
                        parent.right = null;
                        size--;
                    } else {
                        parent.left = null;
                        size--;
                    }
                } else if (parent.left != null && parent.right == null) {
                    parent = parent.left;
                    size--;
                } else if (parent.left == null && parent.right != null) {
                    parent = parent.right;
                    size--;
                } else {
                    Node max = parent.left.findMax();
                    parent = max;
                    size--;
                }
            } else if (compare(parent.data, data) < 0) {
                try {
                    if (compare(parent.left.data, data) == 0) {
                        if (parent.left.left == null && parent.left.right == null) {
                            if (compare(parent.left.data, data) > 0) {
                                parent.right = null;
                                size--;
                            } else {
                                parent.left = null;
                                size--;
                            }
                        } else if (parent.left.left != null && parent.left.right == null) {
                            parent.left = parent.left.left;
                            size--;
                        } else if (parent.left.left == null && parent.left.right != null) {
                            parent.right = parent.left.right;
                            size--;
                        } else {
                            Node max = parent.left.left.findMax();
                            this.left = max;
                            size--;
                        }
                    } else {
                        left.remove(data, parent);
                    }
                } catch (NullPointerException naught) {

                }
            } else if (compare(parent.data, data) > 0) {
                try {
                    if (compare(parent.right.data, data) == 0) {
                        if (parent.right.left == null && parent.right.right == null) {
                            if (compare(parent.data, data) > 0) {
                                parent.right = null;
                                size--;
                            } else {
                                parent.left = null;
                                size--;
                            }
                        } else if (parent.right.left != null && parent.right.right == null) {
                            parent = parent.left;
                            size--;
                        } else if (parent.right.left == null && parent.right.right != null) {
                            parent = parent.right;
                            size--;
                        } else {
                            Node max = parent.right.left.findMax();
                            this.right = max;
                            size--;
                        }
                    } else {
                        right.remove(data, parent);
                    }
                } catch (NullPointerException naught) {

                }
            } else {

            }
        }

        public boolean find(E data) {
            boolean ans = false;
            if (compare(this.data, data) == 0) {
                return true;
            } else if (compare(this.data, data) < 0) {
                try {
                    if (compare(this.left.data, data) == 0) {
                        ans = true;
                    } else {
                        left.find(data);
                    }
                } catch (NullPointerException naught) {
                    ans = false;
                }
            } else if (compare(this.data, data) > 0) {
                try {
                    if (compare(this.right.data, data) == 0) {
                        ans = true;
                    } else {
                        right.find(data);
                    }
                } catch (NullPointerException naught) {
                    ans = false;
                }
            } else {
                ans = false;
            }

            return ans;
        }

        public Node findMin() {
            Node tmp = root;
            while (tmp.left != null) {
                tmp = tmp.left;
            }

            return tmp;
        }

        public Node findMax() {
            Node tmp = root;
            while (tmp.right != null) {
                tmp = tmp.right;
            }

            return tmp;
        }

        public boolean isEmpty() {
            if (root == null) {
                return true;
            } else {
                return false;
            }
        }

        public void clear() {
            root = null;
            size = 0;
            /* I love Java's garbage collection */
        }

        public void addAll(ArrayList<E> input) {
            for (E thing : input) {
                add(thing);
            }
        }

        public void print(Traversal enu) { /* may or may not work */
            Node tmp = this;
            switch (enu) {
                case PREORDER:
                    System.out.println(tmp.data);
                    if (left != null) {
                        left.print(enu);
                    }

                    if (right != null) {
                        right.print(enu);
                    }
                    break;
                case INORDER:
                    if (left != null) {
                        left.print(enu);
                    }

                    System.out.println(tmp.data);

                    if (right != null) {
                        right.print(enu);
                    }
                    break;
                case POSTORDER:
                    if (left != null) {
                        left.print(enu);
                    }

                    if (right != null) {
                        right.print(enu);
                    }

                    System.out.println(tmp.data);
                    break;
                }
            }
        }


}

