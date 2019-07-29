package interpreter;
/**
 * Defines the tree structure used for the Parse Tree
 *
 *
 * @author Casey Haynes
 * @class MyTreeNode.java
 * @version 1.0
 * @bugs Level of abstraction is too great for this project. Can't evaluate any recursed values.
 */
import java.util.ArrayList;
import java.util.List;

public class MyTreeNode<Expression>{
    private Expression data = null;
    private List<MyTreeNode> children = new ArrayList<>();
    private MyTreeNode parent = null;

    public MyTreeNode () {
        this.data = null;
    }

    public MyTreeNode(Expression data) {
        this.data = data;
    }

    public void addChild(MyTreeNode child) {
        child.setParent(this);
        this.children.add(child);
    }

    public void addChild(Expression data) {
        MyTreeNode<Expression> newChild = new MyTreeNode<>(data);
        this.addChild(newChild);
    }

    public void addChildren(List<MyTreeNode> children) {
        for(MyTreeNode t : children) {
            t.setParent(this);
        }
        this.children.addAll(children);
    }

    public List<MyTreeNode> getChildren() {
        return children;
    }

    public Expression getData() {
        return data;
    }

    public void setData(Expression data) {
        this.data = data;
    }

    private void setParent(MyTreeNode parent) {
        this.parent = parent;
    }

    /*public MyTreeNode getParent() {
        return parent;
    }*/
}
